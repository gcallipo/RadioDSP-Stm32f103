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
/* Design parameter: (Band Pass start 3600 end 5200 - 51 Taps - 40 db - fs 35150 Hz)
/* CW filter 51 TAP :
/*  Real Measured bandwidth:   < 300 HZ center to 700 Hz
/*
/* NOTE the real measured features are more stringent than calculated
/* due to the MCU implementation.
/**********************************************************************/

const float32_t firCoeffs32_cw_nar[NUM_TAPS_1] =
{
  -0.001087,
-0.001392,
-0.000652,
-0.000001,
-0.000875,
-0.003061,
-0.003895,
-0.000167,
0.008180,
0.015872,
0.014748,
0.000402,
-0.021798,
-0.037256,
-0.031129,
-0.000557,
0.039360,
0.062458,
0.048743,
0.000495,
-0.055435,
-0.083066,
-0.061357,
-0.000199,
0.063938,
0.091038,
0.063938,
-0.000199,
-0.061357,
-0.083066,
-0.055435,
0.000495,
0.048743,
0.062458,
0.039360,
-0.000557,
-0.031129,
-0.037256,
-0.021798,
0.000402,
0.014748,
0.015872,
0.008180,
-0.000167,
-0.003895,
-0.003061,
-0.000875,
-0.000001,
-0.000652,
-0.001392,
-0.001087
};



static float32_t firStateF32_cw_nar[BLOCK_SIZE + NUM_TAPS_1 - 1];

arm_fir_instance_f32 S1;

void init_firFilter1_cmsis_cw_nar(){

  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S1, NUM_TAPS_1, (float32_t *)&firCoeffs32_cw_nar[0], &firStateF32_cw_nar[0], BLOCK_SIZE);

}

float32_t firFilter1_cmsis_cw_nar(float32_t input)
{
   float32_t inputF = input;
    float32_t outF;

	arm_fir_f32(&S1, &inputF, &outF, BLOCK_SIZE);

    return outF;
}
