/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
#include "ECU_layer/button/euc_button.h"

botton_state_t btn1_status=BUTTON_RELEASED;
botton_state_t btn2_status=BUTTON_RELEASED;
button_t btn1={
    .button_connection=BUTTON_ACTIVE_HIGH,
    .button_state=BUTTON_RELEASED,
    .button_pin.port=PORTC_INDEX,
    .button_pin.pin=GPIO_PIN0,
    .button_pin.direction=GPIO_DIRICTION_INPUT,
    .button_pin.logic=GPIO_LOW

};
button_t btn2={
    .button_connection=BUTTON_ACTIVE_HIGH,
    .button_state=BUTTON_RELEASED,
    .button_pin.port=PORTC_INDEX,
    .button_pin.pin=GPIO_PIN1,
    .button_pin.direction=GPIO_DIRICTION_INPUT,
    .button_pin.logic=GPIO_LOW

};
        
dc_motor_t motr1={
  
    .dc_motor_pin[0].port=PORTB_INDEX,
    .dc_motor_pin[0].pin=GPIO_PIN0,
    .dc_motor_pin[0].direction=GPIO_DIRICTION_OUTPUT,
    .dc_motor_pin[0].logic=GPIO_LOW,
    
    .dc_motor_pin[1].port=PORTB_INDEX,
    .dc_motor_pin[1].pin=GPIO_PIN1,
    .dc_motor_pin[1].direction=GPIO_DIRICTION_OUTPUT,
    .dc_motor_pin[1].logic=GPIO_LOW,
};

std_returntype ret=E_NOT_OK; 
int main() {
    ret = dc_motor_intialize(&motr1);
    ret = button_intialize(&btn1);
    ret = button_intialize(&btn2);

    while(1)
    { 
                    ret= dc_motor_move_right(&motr1);
                    __delay_ms(10000);
                    ret= dc_motor_move_left(&motr1);
                    __delay_ms(10000);
      /*  
       ret = read_button_state(&btn1,&btn1_status);
        ret = read_button_state(&btn2,&btn2_status);
        if(btn1_status==BUTTON_PRESSED){
            ret= dc_motor_move_right(&motr1);
        }
        else if(btn2_status==BUTTON_PRESSED){
            
            ret = dc_motor_move_left(&motr1);
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


