/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"

std_returntype ret = E_OK;
button_t btn1={
    .button_connection=BUTTON_ACTIVE_HIGH,
    .button_state=BUTTON_RELEASED,
    .button_pin.port=PORTB_INDEX,
    .button_pin.pin=GPIO_PIN0,
    .button_pin.direction=GPIO_DIRICTION_INPUT,
    .button_pin.logic=GPIO_LOW

};
button_t btn2={
    .button_connection=BUTTON_ACTIVE_HIGH,
    .button_state=BUTTON_RELEASED,
    .button_pin.port=PORTB_INDEX,
    .button_pin.pin=GPIO_PIN1,
    .button_pin.direction=GPIO_DIRICTION_INPUT,
    .button_pin.logic=GPIO_LOW

};
button_t btn3={
    .button_connection=BUTTON_ACTIVE_HIGH,
    .button_state=BUTTON_RELEASED,
    .button_pin.port=PORTB_INDEX,
    .button_pin.pin=GPIO_PIN2,
    .button_pin.direction=GPIO_DIRICTION_INPUT,
    .button_pin.logic=GPIO_LOW

};
led_t led1={.port_name=PORTB_INDEX,.pin=GPIO_PIN3,.led_status=LED_OFF};
led_t led2={.port_name=PORTB_INDEX,.pin=GPIO_PIN4,.led_status=LED_OFF};
led_t led3={.port_name=PORTB_INDEX,.pin=GPIO_PIN5,.led_status=LED_OFF};
led_t led4={.port_name=PORTB_INDEX,.pin=GPIO_PIN6,.led_status=LED_OFF};
botton_state_t state1 = BUTTON_RELEASED;
botton_state_t state2= BUTTON_RELEASED;
botton_state_t state3 = BUTTON_RELEASED;
// Definition Of The calc_dist() Function
spi_t spi_obj={
   .SPI_interruptHandler=NULL, 
  .clk_phase=SPI_CLOCK_PHASE_SELECT_HIGH,
  .clk_polarity =SPI_CLOCK_POLARITY_SELECT_LOW,
  .data_sampled = SPI_DATA_SAMPLED_AT_MIDDLE,
  .spi_mode=SPI_MASTER_MODE_CLK_FOSC_DIV_4  
};
int main(){
    ret = led_intialize(&led1);
    ret = led_intialize(&led2);
    ret = led_intialize(&led3);
    ret = led_intialize(&led4);
    ret = button_intialize(&btn1);
    ret = button_intialize(&btn2);
    ret = button_intialize(&btn3);
    ret = SPI_Init(&spi_obj);
     
    while(1){
        ret = read_button_state(&btn1,&state1);
        ret = read_button_state(&btn2,&state2);
        ret = read_button_state(&btn3,&state3);
        if(state1 == BUTTON_PRESSED){
            ret = SPI_SendByte(&spi_obj,'a');
            ret = led_turn_on(&led1);
            ret = led_turn_off(&led2);
            ret = led_turn_off(&led3);
            ret = led_turn_off(&led4);
        }
        else if(state2 == BUTTON_PRESSED){
            ret = SPI_SendByte(&spi_obj,'b');
            ret = led_turn_off(&led1);
            ret = led_turn_on(&led2);
            ret = led_turn_off(&led3);
            ret = led_turn_off(&led4);            
        }
        else if(state3 == BUTTON_PRESSED){
            ret = SPI_SendByte(&spi_obj,'c');
            ret = led_turn_off(&led1);
            ret = led_turn_off(&led2);
            ret = led_turn_on(&led3);
            ret = led_turn_off(&led4);
        }
            
      
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


