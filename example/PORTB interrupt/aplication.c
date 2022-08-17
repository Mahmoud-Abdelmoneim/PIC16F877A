/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
led_t led1={.port_name=PORTC_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
led_t led2={.port_name=PORTC_INDEX,.pin=GPIO_PIN1,.led_status=LED_OFF};
led_t led3={.port_name=PORTC_INDEX,.pin=GPIO_PIN2,.led_status=LED_OFF};
led_t led4={.port_name=PORTC_INDEX,.pin=GPIO_PIN3,.led_status=LED_OFF};

void RB4_HIGH_APP_ISR(void)
{
    led_turn_on(&led1);
}
void RB4_LOW_APP_ISR(void)
{
    led_turn_off(&led1);
}


void RB5_HIGH_APP_ISR(void)
{
    led_turn_on(&led2);
}
void RB5_LOW_APP_ISR(void)
{
    led_turn_off(&led2);
}


void RB6_HIGH_APP_ISR(void)
{
    led_turn_on(&led3);
}
void RB6_LOW_APP_ISR(void)
{
    led_turn_off(&led3);
}


void RB7_HIGH_APP_ISR(void)
{
    led_turn_on(&led4);
}
void RB7_LOW_APP_ISR(void)
{
    led_turn_off(&led4);
}
 inteerrupt_RBx_t rb_obj1={
     .EXT_InterruptHandler_HIGH=RB4_HIGH_APP_ISR,    
     .EXT_InterruptHandler_LOW=RB4_LOW_APP_ISR,
     .mcu_pin.port=PORTB_INDEX,
     .mcu_pin.pin=GPIO_PIN4,
     .mcu_pin.direction=GPIO_DIRICTION_INPUT,
            
 };
 inteerrupt_RBx_t rb_obj5={
     .EXT_InterruptHandler_HIGH=RB5_HIGH_APP_ISR,    
     .EXT_InterruptHandler_LOW=RB5_LOW_APP_ISR,
     .mcu_pin.port=PORTB_INDEX,
     .mcu_pin.pin=GPIO_PIN5,
     .mcu_pin.direction=GPIO_DIRICTION_INPUT,
            
 };
 
  inteerrupt_RBx_t rb_obj6={
     .EXT_InterruptHandler_HIGH=RB6_HIGH_APP_ISR,    
     .EXT_InterruptHandler_LOW=RB6_LOW_APP_ISR,
     .mcu_pin.port=PORTB_INDEX,
     .mcu_pin.pin=GPIO_PIN6,
     .mcu_pin.direction=GPIO_DIRICTION_INPUT,
            
 };
   inteerrupt_RBx_t rb_obj7={
     .EXT_InterruptHandler_HIGH=RB7_HIGH_APP_ISR,    
     .EXT_InterruptHandler_LOW=RB7_LOW_APP_ISR,
     .mcu_pin.port=PORTB_INDEX,
     .mcu_pin.pin=GPIO_PIN7,
     .mcu_pin.direction=GPIO_DIRICTION_INPUT,
            
 };
std_returntype ret=E_NOT_OK;
int main() {
    application_intialize();
    ret = led_intialize(&led1);
    ret = led_intialize(&led2);
    ret = led_intialize(&led3);
    ret = led_intialize(&led4);
    ret = External_Interrupt_RBx_Init(&rb_obj1);
    ret = External_Interrupt_RBx_Init(&rb_obj5);
    ret = External_Interrupt_RBx_Init(&rb_obj6);
    ret = External_Interrupt_RBx_Init(&rb_obj7);
    while(1)
    { 
      //ret = External_Interrupt_RBx_Init(&rb_obj1); 
       
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


