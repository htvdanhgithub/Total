#include <xc.h>
#include <stdint.h>
#include <pic16f886.h>
#include "adc_pic16.h"


void ADCInit()
{
// 1. Port configuration
    ADC_LM35_TRIS = 1; // Input
    ANSELHbits.ANS13 = 1;
    
// 2. Channel selection
//    ADCON0bits.CHS = 0b01101;
//    ADCON0bits.CHS = 0b00010;
// 3. ADC voltage reference selection
    ADCON1bits.VCFG0 = 0; // VREF+ is connected to AVDD
// 4. ADC conversion clock source
    ADCON0bits.ADCS = 0b11; // FRC (clock supplied from a dedicated RC oscillator)
// 5. Interrupt control
// 6. Result formatting    
    ADCON1bits.ADFM = 1;
// 7. Turn on ADC Module    
    ADCON0bits.ADON = 1;

}
uint16_t ReadADC(uint8_t ch)
{
  ADCON0bits.CHS=ch;

  //Wait for aquisition
  __delay_us(100);

  //Start Conversion
  ADCON0bits.GO=1;

  //Wait for the conversion to complete
  while(ADCON0bits.GO);

  return ((ADRESH<<8)|ADRESL);

}