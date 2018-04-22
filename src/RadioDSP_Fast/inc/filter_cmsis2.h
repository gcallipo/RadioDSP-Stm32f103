/**
  ******************************************************************************
  * @file    fir_cmsis2.h
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   FIR Low pass SSB Filter (< 3500 Hz) - Header file
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#include "arm_math.h"

#ifndef __FILTER_CMSIS2_H
#define __FILTER_CMSIS2_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

/** Define the tap number of fr filter */
#define BLOCK_SIZE_F2   		     1
#define NUM_TAPS_F2   		        9

/** Hold the coefficents  calculated */
extern const float32_t firCoeffs32_2[NUM_TAPS_F2];
void init_firFilter2_cmsis();
float32_t firFilter2_cmsis(float32_t input);


#ifdef __cplusplus
}
#endif
#endif

/**************************************END OF FILE****/
