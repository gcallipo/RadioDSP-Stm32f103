/**
  ******************************************************************************
  * @file    filter_cmsis_cw_nar2.c
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   FIR band pass CW Filter (700 Hz)
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#include "filter_cmsis_cw_nar2.h"
#include "arm_math.h"


/**********************************************************************
/* Calculator used: https://www.arc.id.au/FilterDesign.html
/*
/* Design parameter: (Band Pass start 1000 end 5000 - 41 Taps - 40 db)
/* CW filter 41 TAP :
/*  Real Measured bandwidth:   < 750 HZ center to 700 Hz
/*
/* NOTE the real measured features are more stringent than calculated
/* due to the MCU implementation.
/**********************************************************************/

const float32_t firCoeffs32_cw_nar2[NUM_TAPS_2] = {-0.000914,
-0.002279,
-0.001326,
0.002048,
0.004885,
0.002702,
-0.006578,
-0.019391,
-0.027575,
-0.024357,
-0.011376,
-0.000509,
-0.006971,
-0.036832,
-0.077821,
-0.101976,
-0.081246,
-0.007275,
0.098168,
0.191001,
0.227920,
0.191001,
0.098168,
-0.007275,
-0.081246,
-0.101976,
-0.077821,
-0.036832,
-0.006971,
-0.000509,
-0.011376,
-0.024357,
-0.027575,
-0.019391,
-0.006578,
0.002702,
0.004885,
0.002048,
-0.001326,
-0.002279,
-0.000914};

static float32_t firStateF32_cw_nar2[BLOCK_SIZE2 + NUM_TAPS_2 - 1];

arm_fir_instance_f32 S2;

void init_firFilter2_cmsis_cw_nar(){

  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S2, NUM_TAPS_2, (float32_t *)&firCoeffs32_cw_nar2[0], &firStateF32_cw_nar2[0], BLOCK_SIZE2);

}

float32_t firFilter2_cmsis_cw_nar(float32_t input)
{
	float32_t  *inputF32, *outputF32;
    float32_t   out[1], in[1];
	in[0] =  input;

	inputF32 = &in[0];
	outputF32 = &out[0];

	arm_fir_f32(&S2, inputF32, outputF32, BLOCK_SIZE2);


    return out[0] ;
}
