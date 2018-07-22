/**
  ******************************************************************************
  * @file    main.c
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   Main routine file
  *
  ******************************************************************************
  *
  *                        THE RADIO DSP - PROJECT
  *
  * This project RadioDSP define a experimental open platform to build
  * Real Time filtering and audio digital signal elaboration from
  * a source audio signal in output form radio transceiver or receiver.
  * The RadioDSP firmware define some FIR filter and routines to perform
  * real time Noise Reduction based on various algorithm.
  * The target hardware platform is Stm32f103 - Arm Cortex-M3 based processor.
  *
  * The functions built in the RadioDSP are:
  * Filter BPF CW  NARROW (300 HZ)
  * Filter BPF CW  NARROW (700 Hz)
  * Filter LPF SSB ( < 2400 Hz )
  * Filter LPF SSB ( < 3500 Hz )
  *
  * Noise Reduction (Exponential Moving Average   - 3 levels smoothing)
  * Noise Reduction (Simple Moving Average        - 3 levels smoothing: 8,16,24 samples)
  *
  * NOTE: this is an experimental project and the functions can be changed
  * without any advise.
  *
  * Info to noise reduction algorithms: info: https://en.wikipedia.org/wiki/Moving_average
  *
  * Calculator used for FIR filters: https://www.arc.id.au/FilterDesign.html
  *
  * The RadioDSP use some parts of the ARM Cortex Microcontroller Software
  * Interface Standard (CMSIS).
  * The RadioDSP use some parts of STM32F103 examples by Yohanes Erwin and
  * others examples and projects free and available in the opensource
  * community.
  *
  * The RadioDSP openSource software is released under the license:
  *              Common Creative - Attribution 3.0
  ******************************************************************************
*/
/* ----------------------------------------------------------------------
** Include Files
** ------------------------------------------------------------------- */
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"

#include "arm_math.h"
#include "io_routines.h"
#include "filter_cmsis.h"
#include "filter_cmsis2.h"
#include "filter_cmsis_cw_nar.h"
#include "filter_cmsis_cw_nar2.h"
#include "filter_noise_reduction.h"

// Filter status
volatile uint16_t FILTER0_STATUS=0;
volatile uint16_t FILTER1_STATUS=0;
volatile uint16_t FILTER2_STATUS=0;
volatile uint16_t FILTER3_STATUS=0;

volatile uint16_t BYPASS=0;

volatile uint16_t  adcValue = 0;
volatile float32_t adcValueF = 0;

volatile uint16_t sel_filter_0 = 0;
volatile uint16_t sel_filter_1 = 0;
volatile uint16_t sel_filter_2 = 0;
volatile uint16_t sel_filter_3 = 0;


void blinkDiode(){
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		DelayMs(30);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		DelayMs(30);
}

void decodeFilterStatus (){

        // Make a copy
        uint16_t FILTER0_STATUS_TMP=FILTER0_STATUS;
        uint16_t FILTER1_STATUS_TMP=FILTER1_STATUS;
        uint16_t FILTER2_STATUS_TMP=FILTER2_STATUS;
        uint16_t FILTER3_STATUS_TMP=FILTER3_STATUS;
        uint16_t changed = 0;

		// Check if push any button - active low
		if (sel_filter_0==0)
		{
			FILTER0_STATUS_TMP = (FILTER0_STATUS_TMP ==0)?1:0;
			changed = 1;
		}

		if (sel_filter_1==0)
		{
			FILTER1_STATUS_TMP = (FILTER1_STATUS_TMP ==0)?1:0;
			changed = 1;
		}

	    if (sel_filter_2==0)
		{
			FILTER2_STATUS_TMP ++;
			FILTER2_STATUS_TMP = (FILTER2_STATUS_TMP >2)?0:FILTER2_STATUS_TMP;
			changed = 1;
		}

        if (sel_filter_3==0)
        {
            FILTER3_STATUS_TMP ++;
			FILTER3_STATUS_TMP = (FILTER3_STATUS_TMP >6)?0:FILTER3_STATUS_TMP;
			changed = 1;
        }

        if( (FILTER0_STATUS_TMP + FILTER1_STATUS_TMP + FILTER2_STATUS_TMP + FILTER3_STATUS_TMP) >0){
           BYPASS =1;
        }else{
           BYPASS =0;
        }

        // if any changes ...
        if (changed == 1){
            // Commit change ...
            blinkDiode();
            FILTER0_STATUS = FILTER0_STATUS_TMP;
            FILTER1_STATUS = FILTER1_STATUS_TMP;
            FILTER2_STATUS = FILTER2_STATUS_TMP;
            FILTER3_STATUS = FILTER3_STATUS_TMP;
        }

   return;
}


void chekUserActions(){

    // Read input switch (active low)
        sel_filter_0 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
        sel_filter_1 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
        sel_filter_2 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
        sel_filter_3 = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);

		// Decode filter status
		decodeFilterStatus();

        // If any audio sel_filter is active, then turn on LED
		if (BYPASS==1)
		{
			// Turn on LED (active low)
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		}
		else
		{
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}

}

int main(void)
{
 	// Initialize delay function
	DelayInit();

	// Initialize ADC, PWM, and GPIO
	ADC_Setup();
	PWM_Setup();
	GPIO_Setup();

	init_firFilter1_cmsis();
    init_firFilter2_cmsis();
	init_firFilter1_cmsis_cw_nar();
	init_firFilter2_cmsis_cw_nar();


	while (1)
	{
		chekUserActions();

        // Hihh delay for debounce
		DelayMs(10);
	}
}

 void TIM3_IRQHandler()
{
	// Checks whether the TIM3 interrupt has occurred or not
	if (TIM_GetITStatus(TIM3, TIM_IT_Update))
	{

		// Read ADC value downsize to 10 bit (10-bit PWM)
		adcValue = ADC_Read() >> 2;
		adcValueF = inputConvert(adcValue);

		// CW NARROW work alone
		if (FILTER0_STATUS==1)
		{
            adcValueF = firFilter2_cmsis(adcValueF);
		    adcValueF = firFilter2_cmsis_cw_nar(adcValueF);
            //adcValueF = firFilter1_cmsis(adcValueF);

		}

        // Noise reduction can work with SSB or alone
	    if (FILTER1_STATUS==1)
		{
		    // Variable noise Reduction
		    adcValueF = firFilter2_cmsis(adcValueF);
			adcValueF = firFilter1_cmsis_cw_nar(adcValueF);

		}

		// SSB work alone or woth Noise reduction
		if (FILTER2_STATUS==1)
		{
		    adcValueF = firFilter1_cmsis(adcValueF);
		}

		// SSB work alone or woth Noise reduction
		if (FILTER2_STATUS==2)
		{
		    adcValueF = firFilter2_cmsis(adcValueF);
		}

        // Noise reduction can work with SSB or alone
	    if (FILTER3_STATUS>0 && FILTER3_STATUS<=3)
		{
		    // Variable noise Reduction
		    adcValueF = fnrFilter_n(adcValueF, FILTER3_STATUS);
		}

		 // Noise reduction can work with SSB or alone
	    if (FILTER3_STATUS>3)
		{
		    // Variable noise Reduction
		    adcValueF = fnrFilter_n_Average(adcValueF, FILTER3_STATUS);
		}

		// Write back to PWM (DAC)
		adcValue = outputConvert(adcValueF);
		PWM_Write(adcValue);

		// Clears the TIM3 interrupt pending bit
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
