/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"

 uint16 x1=0;
 uint16 x2=0;
  uint16 x3=0;
adc_confg_t adc0={
    .interruptHandler=NULL,
    .adc_channel=ADC_CHANNEL_AN0,
    .conversion_clock=ADC_CONVERSION_CLOCK_FOCS_DIV_16,
    .result_format=ADC_RESULT_RIGHT
};

std_returntype ret=E_NOT_OK;
int main() {
    application_intialize();
   
    ret = ADC_Init(&adc0);
     
    while(1)
    { 
        ADC_GetConversion_Blocking(&adc0,ADC_CHANNEL_AN2,&x1);
        ADC_GetConversion_Blocking(&adc0,ADC_CHANNEL_AN1,&x2);
        ADC_GetConversion_Blocking(&adc0,ADC_CHANNEL_AN0,&x3);
        
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


