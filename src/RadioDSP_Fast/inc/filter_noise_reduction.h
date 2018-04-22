/**
  ******************************************************************************
  * @file    filter_noise_reduction.h
  * @author  Giuseppe Callipo - IK8YFW - ik8yfw@libero.it
  * @version V1.0.0
  * @date    22-04-2018
  * @brief   Noise Reduction routines
  *
  *
  * NOTE: This file is part of RadioDSP project.
  *       See main.c file for additional project informations.
  ******************************************************************************/

#ifndef FILTER_NOISE_REDUCTION_H_INCLUDED
#define FILTER_NOISE_REDUCTION_H_INCLUDED

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

/* define the max number of samples used on Average filter */
#define MAX_FILTER_BUF 24

extern volatile float outwork_fn;
float  fnrFilter_n(float inwork, uint16_t n);
float  fnrFilter_n_Average(float inwork ,uint16_t n);

#ifdef __cplusplus
}
#endif

#endif /* FILTER_NOISE_REDUCTION_H_INCLUDED */

/**************************************END OF FILE****/
