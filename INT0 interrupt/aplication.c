/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
led_t led1={.port_name=PORTC_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
void INT0_APP_ISR(void){
    led_turn_toggle(&led1);
}

 inteerrupt_INTx_t INT0={
     .EXT_InterruptHandler=INT0_APP_ISR,
     
     .source=INTERRUPT_EXTERNAL_INT0,
     .edge=INTERRUPT_RISING_EDGE,
     .mcu_pin.port=PORTB_INDEX,
     .mcu_pin.pin=GPIO_PIN0,
     .mcu_pin.direction=GPIO_DIRICTION_INPUT,
            
 };
 
std_returntype ret=E_NOT_OK;
int main() {
    application_intialize();
    ret = External_Interrupt_INT0_Init(&INT0);
    led_intialize(&led1);
    
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


