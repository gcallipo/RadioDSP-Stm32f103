/**
  ******************************************************************************
  * @file    fir_cw_nar.h
  * @author  Giuseppe Callipo - IK8YFW
  * @version V1.0.0
  * @date    24-02-2018
  * @brief   FIR Filter LPF CW narrow.
  *
  *
  * FIR FILTER LPF CW NARROW :
  * Measured gain @ 800 Hz width: 500 Hz circa
  *
  * FIR filter designed with
  * http://t-filter.appspot.com
  *
  * sampling frequency: 35100 Hz
  *
  * 0 Hz - 3000 Hz
  *  gain = 1
  *  desired ripple = 5 dB
  *  actual ripple = 25.824329357410395 dB
  *
  * * 3100 Hz - 17550 Hz
  *  gain = 0
  *  desired attenuation = -40 dB
  *  actual attenuation = -28.342362373187107 dB
  *
  ******************************************************************************
*/

#ifndef __FILTER_CW_NAR_H
#define __FILTER_CW_NAR_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

/** Define the tap number of fr filter */
#define FILTER_BUF   		32

/** Hold the coefficents  calculated */
extern const float filter_coeff[FILTER_BUF];
uint16_t firFilter1(uint16_t input);

#ifdef __cplusplus
}
#endif
#endif

/**************************************END OF FILE****/
