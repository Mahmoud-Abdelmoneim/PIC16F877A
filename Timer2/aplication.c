/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
volatile uint8 flag=0;
led_t led1={.port_name=PORTD_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
timer2_t timer2_obj;


void Timer2(void){
    flag++;
    led_turn_toggle(&led1);
    
    
}


std_returntype ret=E_NOT_OK; 
int main() {
    application_intialize();
    timer2_obj.TIMER2_InterruptHandler=Timer2;
    timer2_obj.perscaler_value=TIMER2_PRESCALER_DIV_BY_16;
    timer2_obj.postscaler_value=TIMER2_POSTCALER_DIV_BY_13;
    timer2_obj.timer2_preload_value=240;
    ret =led_intialize(&led1);
    ret = Timer2_Init(&timer2_obj);
    while(1)
    { 
       
        
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


