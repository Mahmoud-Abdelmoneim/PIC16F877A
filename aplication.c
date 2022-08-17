/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"

std_returntype ret = E_OK;
led_t led1={.port_name=PORTB_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
led_t led2={.port_name=PORTB_INDEX,.pin=GPIO_PIN1,.led_status=LED_OFF};
led_t led3={.port_name=PORTB_INDEX,.pin=GPIO_PIN2,.led_status=LED_OFF};
led_t led4={.port_name=PORTB_INDEX,.pin=GPIO_PIN3,.led_status=LED_OFF};

uint8 counter=0;
void Timer0();
timer0_t timer0={
  .Timer0_InterruptHandler =Timer0,
  .perscaler_enable=TIMER0_PERSCALER_DISABLE_CFG,
  .prescaler_value=TIM0_PRESCALER_DIV_2,
  .timer0_counter_edge=TIMER0_RISING_EDGE,
  .timer0_mode=TIMER0_TIMER_MODE,
  .timer0_preload_value=56
  
};
void Timer0(){
    TMR0=56;
    counter++;
    if(counter == 4)
    {
        led_turn_off(&led1);
    }
    else if(counter == 80)
    {
        led_turn_on(&led1);
        counter=0;
    }
    
}
int main(){
    Timer0_Init(&timer0);
    led_intialize(&led1);
    while(1){
        
   
   
    }
         
    return (EXIT_SUCCESS);
}



void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


