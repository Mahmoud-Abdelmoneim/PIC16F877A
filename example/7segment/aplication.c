/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
segment_t seg1={
    .segment_pin[0].direction=GPIO_DIRICTION_OUTPUT,
    .segment_pin[0].port=PORTC_INDEX,
    .segment_pin[0].pin=GPIO_PIN0,
    .segment_pin[0].logic=GPIO_LOW,
    
    .segment_pin[1].direction=GPIO_DIRICTION_OUTPUT,
    .segment_pin[1].port=PORTC_INDEX,
    .segment_pin[1].pin=GPIO_PIN1,
    .segment_pin[1].logic=GPIO_LOW,
    
    .segment_pin[2].direction=GPIO_DIRICTION_OUTPUT,
    .segment_pin[2].port=PORTC_INDEX,
    .segment_pin[2].pin=GPIO_PIN2,
    .segment_pin[2].logic=GPIO_LOW,
    
    .segment_pin[3].direction=GPIO_DIRICTION_OUTPUT,
    .segment_pin[3].port=PORTC_INDEX,
    .segment_pin[3].pin=GPIO_PIN3,
    .segment_pin[3].logic=GPIO_LOW,
    
    .segment_type=SEGMENT_COMMON_ANODE

};

std_returntype ret=E_NOT_OK;
int main() {
    application_intialize();
   
    
    while(1)
    { 
       ret = seven_seg_write_number(&seg1,9);
      
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    seven_seg_intialize(&seg1);
 
}

