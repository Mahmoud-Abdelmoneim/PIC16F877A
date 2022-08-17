/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
#include "ECU_layer/LCD_CHAR/ecu_lcd_char.h"

std_returntype ret=E_NOT_OK; 

char_4bit_lcd_t lcd1={
    .lcd_rs.port=PORTC_INDEX,
    .lcd_rs.pin=GPIO_PIN2,
    .lcd_rs.direction=GPIO_DIRICTION_OUTPUT,
    .lcd_rs.logic=GPIO_LOW,
    .lcd_en.port=PORTC_INDEX,
    .lcd_en.pin=GPIO_PIN3,
    .lcd_en.direction=GPIO_DIRICTION_OUTPUT,
    .lcd_en.logic=GPIO_LOW,
    .lcd_data[0].port=PORTC_INDEX,
    .lcd_data[0].pin=GPIO_PIN4,
    .lcd_data[0].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[0].logic=GPIO_LOW,
    .lcd_data[1].port=PORTC_INDEX,
    .lcd_data[1].pin=GPIO_PIN5,
    .lcd_data[1].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[1].logic=GPIO_LOW,
    .lcd_data[2].port=PORTC_INDEX,
    .lcd_data[2].pin=GPIO_PIN6,
    .lcd_data[2].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[2].logic=GPIO_LOW,
    .lcd_data[3].port=PORTC_INDEX,
    .lcd_data[3].pin=GPIO_PIN7,
    .lcd_data[3].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[3].logic=GPIO_LOW,
    
};
char_8bit_lcd_t lcd2={
    .lcd_rs.port=PORTB_INDEX,
    .lcd_rs.pin=GPIO_PIN0,
    .lcd_rs.direction=GPIO_DIRICTION_OUTPUT,
    .lcd_rs.logic=GPIO_LOW,
    
    .lcd_en.port=PORTB_INDEX,
    .lcd_en.pin=GPIO_PIN1,
    .lcd_en.direction=GPIO_DIRICTION_OUTPUT,
    .lcd_en.logic=GPIO_LOW,
    
    .lcd_data[0].port=PORTB_INDEX,
    .lcd_data[0].pin=GPIO_PIN2,
    .lcd_data[0].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[0].logic=GPIO_LOW,
    .lcd_data[1].port=PORTB_INDEX,
    .lcd_data[1].pin=GPIO_PIN3,
    .lcd_data[1].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[1].logic=GPIO_LOW,
    .lcd_data[2].port=PORTB_INDEX,
    .lcd_data[2].pin=GPIO_PIN4,
    .lcd_data[2].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[2].logic=GPIO_LOW,
    .lcd_data[3].port=PORTB_INDEX,
    .lcd_data[3].pin=GPIO_PIN5,
    .lcd_data[3].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[3].logic=GPIO_LOW,
    .lcd_data[4].port=PORTB_INDEX,
    .lcd_data[4].pin=GPIO_PIN6,
    .lcd_data[4].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[4].logic=GPIO_LOW,
    .lcd_data[5].port=PORTB_INDEX,
    .lcd_data[5].pin=GPIO_PIN7,
    .lcd_data[5].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[5].logic=GPIO_LOW,
    .lcd_data[6].port=PORTC_INDEX,
    .lcd_data[6].pin=GPIO_PIN0,
    .lcd_data[6].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[6].logic=GPIO_LOW,
    .lcd_data[7].port=PORTC_INDEX,
    .lcd_data[7].pin=GPIO_PIN1,
    .lcd_data[7].direction=GPIO_DIRICTION_OUTPUT,
    .lcd_data[7].logic=GPIO_LOW
    
};
int main() {
    ret = lcd_4bit_initialize(&lcd1);
    ret = lcd_8bit_initialize(&lcd2);
    ret = lcd_4bit_send_string(&lcd1,"hello all");
    uint8 counter;
    while(1)
    {
        for(counter = 1;counter<11;counter++){
           
            ret = lcd_4bit_send_string_pos(&lcd1,2,counter,"Ahmed");
            
            __delay_ms(250);
            ret = lcd_4bit_send_char_data_pos(&lcd1,2,counter,' ');
        }
        for(counter = 11;counter>1;counter--){
            
            ret = lcd_4bit_send_string_pos(&lcd1,2,counter,"Ahmed");
            
            __delay_ms(250);
            ret = lcd_4bit_send_char_data_pos(&lcd1,2,counter+4,' ');
            
        }
        

    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


