/**
  ******************************************************************************
  * @file    filter_cmsis_cw_nar2.h
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   FIR band pass CW Filter (700 Hz) - Header file
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#include "arm_math.h"

#ifndef __FILTER_CMSIS_CW_NAR2_H
#define __FILTER_CMSIS_CW_NAR2_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

/** Define the tap number of fr filter */
#define BLOCK_SIZE2   		1
#define NUM_TAPS_2   		41

/** Hold the coefficents  calculated */
extern const float32_t firCoeffs32_cw_nar2[NUM_TAPS_2];
void init_firFilter2_cmsis_cw_nar();
float32_t firFilter2_cmsis_cw_nar(float32_t input);

#ifdef __cplusplus
}
#endif
#endif

/**************************************END OF FILE****/
