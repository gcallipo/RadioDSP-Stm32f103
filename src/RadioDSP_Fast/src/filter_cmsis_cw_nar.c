/**
  ******************************************************************************
  * @file    filter_cmsis_cw_nar.c
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   FIR band pass CW Filter (300 Hz)
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#include "filter_cmsis_cw_nar.h"
#include "arm_math.h"

/**********************************************************************
/* Calculator used: https://www.arc.id.au/FilterDesign.html
/*
/* Design parameter: (Band Pass start 2500 end 4000 - 61 Taps - 40 db)
/* CW filter 61 TAP :
/*  Real Measured bandwidth:   < 300 HZ center to 700 Hz
/*
/* NOTE the real measured features are more stringent than calculated
/* due to the MCU implementation.
/**********************************************************************/

const float32_t firCoeffs32_cw_nar[NUM_TAPS_1] = {-0.002491,
-0.002638,
-0.001074,
0.002126,
0.005692,
0.007642,
0.006446,
0.002186,
-0.003160,
-0.006734,
-0.006654,
-0.003528,
-0.000406,
-0.000830,
-0.006003,
-0.012965,
-0.015439,
-0.007469,
0.011960,
0.036266,
0.052901,
0.049322,
0.020524,
-0.026099,
-0.072035,
-0.095378,
-0.081663,
-0.032213,
0.034769,
0.091609,
0.113798,
0.091609,
0.034769,
-0.032213,
-0.081663,
-0.095378,
-0.072035,
-0.026099,
0.020524,
0.049322,
0.052901,
0.036266,
0.011960,
-0.007469,
-0.015439,
-0.012965,
-0.006003,
-0.000830,
-0.000406,
-0.003528,
-0.006654,
-0.006734,
-0.003160,
0.002186,
0.006446,
0.007642,
0.005692,
0.002126,
-0.001074,
-0.002638,
-0.002491};



static float32_t firStateF32_cw_nar[BLOCK_SIZE + NUM_TAPS_1 - 1];

arm_fir_instance_f32 S1;

void init_firFilter1_cmsis_cw_nar(){

  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S1, NUM_TAPS_1, (float32_t *)&firCoeffs32_cw_nar[0], &firStateF32_cw_nar[0], BLOCK_SIZE);

}

float32_t firFilter1_cmsis_cw_nar(float32_t input)
{
	float32_t  *inputF32, *outputF32;
    float32_t   out[1], in[1];
	in[0] = input;

	inputF32 = &in[0];
	outputF32 = &out[0];

	arm_fir_f32(&S1, inputF32, outputF32, BLOCK_SIZE);

    return out[0];
}
