/**
  ******************************************************************************
  * @file    main.c
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   IO Routine
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#ifndef IO_ROUTINES_H_INCLUDED
#define IO_ROUTINES_H_INCLUDED


#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"
#include "arm_math.h"

/********************************************************************
 *
 *                   VARIABLES
 *
 ********************************************************************/

extern volatile uint16_t  adcValue;
extern volatile float32_t adcValueF;

void PWM_Setup();
void PWM_Write(uint16_t val);
void ADC_Setup();
uint16_t ADC_Read();
void GPIO_Setup();
void SysTick_Handler();
void DelayInit();
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);
float32_t inputConvert(uint16_t input);
uint16_t outputConvert(float32_t input);

#ifdef __cplusplus
}
#endif


#endif /* IO_ROUTINES_H_INCLUDED */

/**************************************END OF FILE****/
