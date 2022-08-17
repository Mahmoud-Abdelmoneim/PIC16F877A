/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
volatile uint8 flag=0;
uint8 read=0;
led_t led1={.port_name=PORTC_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
void Timer0(void){
    flag++;
    led_turn_toggle(&led1);
    if(flag==15){
        led_turn_toggle(&led1);
        flag=0;
    }
}
timer0_t timer0={
  .Timer0_InterruptHandler =Timer0,
  .perscaler_enable=TIMER0_PERSCALER_ENABLE_CFG,
  .prescaler_value=TIM0_PRESCALER_DIV_256,
  .timer0_counter_edge=TIMER0_RISING_EDGE,
  .timer0_mode=TIMER0_TIMER_MODE,
  .timer0_preload_value=0
  
};
timer0_t timer0_counter={
  .Timer0_InterruptHandler =Timer0,
  .perscaler_enable=TIMER0_PERSCALER_DISABLE_CFG,
  
  .timer0_counter_edge=TIMER0_RISING_EDGE,
  .timer0_mode=TIMER0_COUNTER_MODE,
  .timer0_preload_value=0
  
};
std_returntype ret=E_NOT_OK;
int main() {
    application_intialize();
    ret =led_intialize(&led1);
    //ret = Timer0_Init(&timer0);
    ret = Timer0_Init(&timer0_counter);
    while(1)
    { 
       Timer0_Read_Value(&timer0_counter,&read);
        
        
        
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


