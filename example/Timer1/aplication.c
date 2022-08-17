/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
//volatile uint8 flag=0;
volatile uint16 flag=0; 
volatile uint16 counter=0;
led_t led1={.port_name=PORTD_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
timer1_t conter_obj;
void Timer1(void){
    
    led_turn_toggle(&led1);
    flag++;
    
}
void timer1_timer_init(void ){
    timer1_t timer1_obj;
    timer1_obj.TIMER1_InterruptHandler=Timer1;
    timer1_obj.perscaler_value=TIMER1_PRESCALER_DIV_BY_2;
    timer1_obj.timer1_mode=TIMER1_TIMER_MODE;
   // timer1_obj.timer1_osc_cfg=RIMER1_OCS_DISABLE;
    timer1_obj.timer1_preload_value=15536;
    Timer1_Init(&timer1_obj);
}

std_returntype ret=E_NOT_OK; 
int main() {
    application_intialize();
    ret =led_intialize(&led1);
     conter_obj.TIMER1_InterruptHandler=Timer1;
    conter_obj.perscaler_value=TIMER1_PRESCALER_DIV_BY_1;
    conter_obj.timer1_mode=TIMER1_COUNTER_MODE;
    conter_obj.timer1_osc_cfg=RIMER1_OCS_DISABLE;
    conter_obj.timer1_preload_value=0;
    conter_obj.timer1_counter_mode=TIMER1_SYN_COUNTER_MODE;
    Timer1_Init(&conter_obj);
   
    while(1)
    { 
       
       Timer1_Read_Value(&conter_obj,&counter); 
        
        
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


