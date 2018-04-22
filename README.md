# RadioDSP-Stm32f103

                          THE RADIO DSP - PROJECT
  
   This project RadioDSP define a experimental open platform to build
   Real Time filtering and audio digital signal elaboration from
   a source audio signal in output form radio transceiver or receiver.
   The RadioDSP firmware define some FIR filter and routines to perform
   real time Noise Reduction based on various algorithm.
   The target hardware platform is Stm32f103 - Arm Cortex-M3 based processor.
  
   The functions built in the RadioDSP are:
   
    * Filter BPF CW  NARROW (300 HZ)
    * Filter BPF CW  NARROW (700 Hz)
    * Filter LPF SSB ( < 2400 Hz )
    * Filter LPF SSB ( < 3500 Hz )
    * Noise Reduction (Exponential Moving Average   - 3 levels smoothing)
    * Noise Reduction (Simple Moving Average        - 3 levels smoothing: 8,16,24 samples)
  
   NOTE: this is an experimental project and the functions can be changed
   without any advise.
  
     Info to noise reduction algorithms: info: https://en.wikipedia.org/wiki/Moving_average
     Calculator used for FIR filters: https://www.arc.id.au/FilterDesign.html
  
   The RadioDSP use some parts of the ARM Cortex Microcontroller Software
   Interface Standard (CMSIS).
   The RadioDSP use some parts of STM32F103 examples by Yohanes Erwin and
   others examples and projects free and available in the opensource
   community.
  
     The RadioDSP openSource software is released under the license:
                Common Creative - Attribution 3.0
