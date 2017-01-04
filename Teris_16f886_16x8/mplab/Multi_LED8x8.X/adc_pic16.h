/* 
 * File:   adc_pic16.h
 * Author: Avinash Gupta
 *
 * Created on June 8, 2013, 6:59 PM
 */

#ifndef ADC_PIC16_H
#define	ADC_PIC16_H

#include <xc.h>
#include <stdint.h>
#include "myutils.h"

#ifdef	__cplusplus
extern "C" {
#endif
//LM35 in (LM35)
//LM35 is connected to Port A bit 2
#define ADC_LM35_PORT      B
#define ADC_LM35_POS       5
#define ADC_LM35_AN        13
    
#define ADC_LM35           PORTBIT(ADC_LM35_PORT, ADC_LM35_POS)
#define ADC_LM35_TRIS      TRISBIT(ADC_LM35_PORT, ADC_LM35_POS)
#define ADC_LM35_PIN       PIN(ADC_LM35_PORT, ADC_LM35_POS)

    
void ADCInit();
uint16_t ReadADC(uint8_t ch);




#ifdef	__cplusplus
}
#endif

#endif	/* ADC_PIC16_H */

