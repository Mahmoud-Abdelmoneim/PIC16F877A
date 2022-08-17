/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"

dc_motor_t dc_motor1={
        .dc_motor_pin[0].port=PORTC_INDEX,
        .dc_motor_pin[0].pin=GPIO_PIN0,
        .dc_motor_pin[0].logic=DC_MOTOR_OFF_STATUS ,
        .dc_motor_pin[0].direction=GPIO_DIRICTION_OUTPUT,
        
        .dc_motor_pin[1].port=PORTC_INDEX,
        .dc_motor_pin[1].pin=GPIO_PIN1,
        .dc_motor_pin[1].logic=DC_MOTOR_OFF_STATUS ,
        .dc_motor_pin[1].direction=GPIO_DIRICTION_OUTPUT,

};

dc_motor_t dc_motor2={
        .dc_motor_pin[0].port=PORTC_INDEX,
        .dc_motor_pin[0].pin=GPIO_PIN2,
        .dc_motor_pin[0].logic=DC_MOTOR_OFF_STATUS ,
        .dc_motor_pin[0].direction=GPIO_DIRICTION_OUTPUT,

        .dc_motor_pin[1].port=PORTC_INDEX,
        .dc_motor_pin[1].pin=GPIO_PIN3,
        .dc_motor_pin[1].logic=DC_MOTOR_OFF_STATUS ,
        .dc_motor_pin[1].direction=GPIO_DIRICTION_OUTPUT,

};





std_returntype ret=E_NOT_OK;
int main() {
    application_intialize();
   
    
    while(1)
    { 
        ret=dc_motor_move_right(&dc_motor1);
        ret=dc_motor_move_right(&dc_motor2);
        __delay_ms(2000);
        ret=dc_motor_move_left(&dc_motor1);
        ret=dc_motor_move_left(&dc_motor2);
        __delay_ms(2000);
        dc_motor_stop(&dc_motor1);
        dc_motor_stop(&dc_motor2);
        __delay_ms(2000);
        ret=dc_motor_move_right(&dc_motor1);
        ret=dc_motor_move_left(&dc_motor2);
        __delay_ms(2000);
         dc_motor_stop(&dc_motor1);
        dc_motor_stop(&dc_motor2);
        __delay_ms(2000);
        ret=dc_motor_move_right(&dc_motor2);
        ret=dc_motor_move_left(&dc_motor1);
        __delay_ms(2000);
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    ret=dc_motor_intialize(&dc_motor1);
    ret=dc_motor_intialize(&dc_motor2);
}

