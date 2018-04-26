/**
  ******************************************************************************
  * @file    filter_cmsis.c
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   FIR Low pass SSB Filter (< 2400)
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#include "filter_cmsis.h"
#include "arm_math.h"

/************************************************************
/*  Calculator used: https://www.arc.id.au/FilterDesign.html
/*  Design parameters: (Low Pass end 4000 - 11 Taps - 40 db - fs 35150 Hz)
/*
/*  Real Measured bandwidth: 0 - <2400 Hz
/* NOTE the real measured features are more stringent than calculated
/* due to the MCU implementation.
/************************************************************/

const float32_t firCoeffs32[NUM_TAPS] = {
-0.004000,
0.007546,
0.051188,
0.124688,
0.197326,
0.227920,
0.197326,
0.124688,
0.051188,
0.007546,
-0.004000
};

static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

arm_fir_instance_f32 S;

void init_firFilter1_cmsis(){

  /* Call FIR init function to initialize the instance structure. */
  arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], BLOCK_SIZE);

}

float32_t firFilter1_cmsis(float32_t input)
{

    float32_t inputF = input;
    float32_t outF;

	arm_fir_f32(&S, &inputF, &outF, BLOCK_SIZE);

    return outF;
}
