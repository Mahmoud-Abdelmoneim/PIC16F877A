/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
 void ADC1_ISR();
 uint16 y0=0;
 uint16 y1=0;
 uint16 y2=0;
 //volatile uint8 adc_flag;
 uint8 adc_req=0; 

adc_confg_t adc0={
    .interruptHandler=ADC1_ISR,
    .adc_channel=ADC_CHANNEL_AN0,
    .conversion_clock=ADC_CONVERSION_CLOCK_FOCS_DIV_16,
    .result_format=ADC_RESULT_RIGHT
};
  void ADC1_ISR()
{
      std_returntype ret=E_NOT_OK;
     if(0==adc_req)
        {
            ret = ADC_GetConversionResult(&adc0,&y0);
            adc_req=1;
        }
        else if(1==adc_req)
        {
           ret = ADC_GetConversionResult(&adc0,&y1);
           adc_req=2;
        } 
        else if(2==adc_req)
        {
            ret = ADC_GetConversionResult(&adc0,&y2);
            adc_req=0;
        }
      
      
      
}


std_returntype ret=E_NOT_OK;
int main() {
    application_intialize();
   
    ret = ADC_Init(&adc0);
     
    while(1)
    { 
        if(0==adc_req)
        {
            ADC_StartConversion_Interrupt(&adc0,ADC_CHANNEL_AN0);
            
            
        }
        else if(1==adc_req)
        {
            ADC_StartConversion_Interrupt(&adc0,ADC_CHANNEL_AN1);
            
        } 
        else if(2==adc_req)
        {
            ADC_StartConversion_Interrupt(&adc0,ADC_CHANNEL_AN2);
            
        }
        
        
        
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


