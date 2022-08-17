/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
void spi_interrupt(void);
led_t led1={.port_name=PORTB_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
led_t led2={.port_name=PORTB_INDEX,.pin=GPIO_PIN1,.led_status=LED_OFF};
led_t led3={.port_name=PORTB_INDEX,.pin=GPIO_PIN2,.led_status=LED_OFF};
led_t led4={.port_name=PORTB_INDEX,.pin=GPIO_PIN3,.led_status=LED_OFF};


uint8 data_read=0;
std_returntype ret = E_OK;


// Definition Of The calc_dist() Function
spi_t spi_obj={
   .SPI_interruptHandler=spi_interrupt, 
  .clk_phase=SPI_CLOCK_PHASE_SELECT_HIGH,
  .clk_polarity =SPI_CLOCK_POLARITY_SELECT_LOW,
  .data_sampled = SPI_DATA_SAMPLED_AT_MIDDLE,
  .spi_mode=SPI_SLAVE_MODE_SS_PIN_ENABLED  
};
void spi_interrupt(void){
    SPI_ReadByte(&spi_obj,&data_read);
    
}
int main(){
    ret = led_intialize(&led1);
    ret = led_intialize(&led2);
    ret = led_intialize(&led3);
    ret = led_intialize(&led4);
    ret = SPI_Init(&spi_obj);
     
    while(1){
        if(data_read == 'a'){
            ret = led_turn_on(&led1);
            ret = led_turn_off(&led2);
            ret = led_turn_off(&led3);
            ret = led_turn_off(&led4);
        }
            
        if(data_read== 'b'){
            ret = led_turn_off(&led1);
            ret = led_turn_on(&led2);
            ret = led_turn_off(&led3);
            ret = led_turn_off(&led4);
            
        }
        if(data_read== 'b'){
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


