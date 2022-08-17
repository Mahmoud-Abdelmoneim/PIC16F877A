/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
ccp_t pwm;
ccp_t pwm1;
timer2_t tmr2_obj;
std_returntype ret=E_NOT_OK; 
int main() {
    
    //pwm.CCP1_InterruptHandler=NULL;
    pwm.ccp_inst=CCP2_INST;
    pwm.ccp_mode=CCP_PWM_MODE_SELECTED;
    pwm.ccp_mode_variant=CCP_PWM_MODE;
    pwm.freq_pmw=20000;
    pwm.ccp_pin.port=PORTC_INDEX;
    pwm.ccp_pin.pin=GPIO_PIN1;
    pwm.ccp_pin.direction=GPIO_DIRICTION_OUTPUT;
    
    pwm.perscaler_value = CCP_PRESCALER_DIV_BY_1;
    pwm.postscaler_value = CCP_POSTCALER_DIV_BY_1;
    
    //pwm1.CCP1_InterruptHandler=NULL;
    pwm1.ccp_inst=CCP1_INST;
    pwm1.ccp_mode=CCP_PWM_MODE_SELECTED;
    pwm1.ccp_mode_variant=CCP_PWM_MODE;
    pwm1.freq_pmw=20000;
    pwm1.ccp_pin.port=PORTC_INDEX;
    pwm1.ccp_pin.pin=GPIO_PIN2;
    pwm1.ccp_pin.direction=GPIO_DIRICTION_OUTPUT;
    
    pwm1.perscaler_value = CCP_PRESCALER_DIV_BY_1;
    pwm1.postscaler_value = CCP_POSTCALER_DIV_BY_1;
     ret = CCP_Init(&pwm);
     ret = CCP_Init(&pwm1);
    tmr2_obj.perscaler_value=TIMER2_PRESCALER_DIV_BY_1;
    tmr2_obj.postscaler_value=TIMER2_POSTCALER_DIV_BY_1;
    tmr2_obj.timer2_preload_value=0;
   
    ret =  Timer2_Init(&tmr2_obj);
    ret = CCP_PWM_Set_duty(&pwm,50);
     ret = CCP_PWM_Set_duty(&pwm1,75);
    ret = CCP_PWM_Sart(&pwm1);
    ret = CCP_PWM_Sart(&pwm);
    while(1)
    { /*
        for(int i=0;i<100;i+=5){
          ret = CCP_PWM_Set_duty(&pwm,i);  
          __delay_ms(100);
        } 
        */
        
        
        
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


