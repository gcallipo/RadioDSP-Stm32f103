/**
  ******************************************************************************
  * @file     filter_cmsis2.c
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   FIR Low pass SSB Filter (< 3500)
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#include "filter_cmsis2.h"
#include "arm_math.h"

/************************************************************
/*  Calculator used: https://www.arc.id.au/FilterDesign.html
/*  Design parameters: (Low Pass end 5500 - 9 Taps - 40 db - fs 35150 Hz)
/*
/*  Real Measured bandwidth: 0 - <3500 Hz
/* NOTE the real measured features are more stringent than calculated
/* due to the MCU implementation.
/************************************************************/

const float32_t firCoeffs32_2[NUM_TAPS_F2] = {
-0.008419,
0.007975,
0.100966,
0.242400,
0.313390,
0.242400,
0.100966,
0.007975,
-0.008419
};

static float32_t firStateF32_2[BLOCK_SIZE_F2 + NUM_TAPS_F2 - 1];

arm_fir_instance_f32 S_2;

void init_firFilter2_cmsis(){

  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S_2, NUM_TAPS_F2, (float32_t *)&firCoeffs32_2[0], &firStateF32_2[0], BLOCK_SIZE_F2);

}

float32_t firFilter2_cmsis(float32_t input)
{

    float32_t inputF = input;
    float32_t outF;

	arm_fir_f32(&S_2, &inputF, &outF, BLOCK_SIZE_F2);

    return outF;
}
