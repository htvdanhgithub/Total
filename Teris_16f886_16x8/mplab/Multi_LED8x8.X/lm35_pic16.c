#include <xc.h>
#include <stdint.h>

#include "adc_pic16.h"
#include "lm35_pic16.h"


int LM35ReadTemp()
{
    //Temperature
    float t;

    //Read ADC
    uint16_t adc_value=ReadADC(ADC_LM35_AN);
//    __delay_us(100);
//
//    adc_value+=ReadADC(ADC_LM35_AN);
//    __delay_us(100);
//
//     adc_value+=ReadADC(ADC_LM35_AN);
//    __delay_us(100);
//
//    adc_value=adc_value/3;

    //Convert to degree Centrigrade
//    t=((adc_value/1023.00)*500.00);

    return (int)(adc_value*0.4887);
}

