/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
#include "ECU_layer/ecu_ultrasonic_sensor/ecu_ultrasonic_sensor.h"
std_returntype ret = E_OK;
// Definition Of The calc_dist() Function
led_t led1={.port_name=PORTC_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
led_t led2={.port_name=PORTC_INDEX,.pin=GPIO_PIN1,.led_status=LED_OFF};
led_t led3={.port_name=PORTC_INDEX,.pin=GPIO_PIN2,.led_status=LED_OFF};
led_t led4={.port_name=PORTC_INDEX,.pin=GPIO_PIN3,.led_status=LED_OFF};
uint8 distance=0;
ultrasonic_t ultrasonic={
  .echo.port=PORTB_INDEX,
  .echo.pin = GPIO_PIN0,
  .echo.direction = GPIO_DIRICTION_INPUT,
  .echo.logic = GPIO_LOW,  
  
  .trigger.port=PORTB_INDEX,
  .trigger.pin = GPIO_PIN1,
  .trigger.direction = GPIO_DIRICTION_OUTPUT,
  .trigger.logic = GPIO_LOW
};
uint16 dist=0;
int main(){
    ret = Ultrasonic_Init(&ultrasonic);
    ret = led_intialize(&led1);
    ret = led_intialize(&led2);
    ret = led_intialize(&led3);
    ret = led_intialize(&led4);
    
    while(1){
       ret = Ultrasonic_calculate_Distance(&ultrasonic,&dist);
       
       if(dist==7){
               ret = led_turn_on(&led1);
               ret = led_turn_off(&led2);
               ret = led_turn_off(&led3);
               ret = led_turn_off(&led4);
               __delay_ms(50);
       }
       if(dist == 12 ){
               ret = led_turn_on(&led1);
               ret = led_turn_on(&led2);
               ret = led_turn_off(&led3);
               ret = led_turn_off(&led4); 
               __delay_ms(50);
       }
       if(dist == 17){
               ret = led_turn_on(&led1);
               ret = led_turn_on(&led2);
               ret = led_turn_on(&led3);
               ret = led_turn_off(&led4);
               __delay_ms(50);
       }
       if(dist==22){
               ret = led_turn_on(&led1);
               ret = led_turn_on(&led2);
               ret = led_turn_on(&led3);
               ret = led_turn_on(&led4);  
               __delay_ms(50);
       }
       else{
               ret = led_turn_off(&led1);
               ret = led_turn_off(&led2);
               ret = led_turn_off(&led3);
               ret = led_turn_off(&led4); 
               __delay_ms(50);
       }
           
       /*
       switch(dist){
           case 5:
               ret = led_turn_on(&led1);
               ret = led_turn_off(&led2);
               ret = led_turn_off(&led3);
               ret = led_turn_off(&led4);
               break;
           case 10:
               ret = led_turn_on(&led1);
               ret = led_turn_on(&led2);
               ret = led_turn_off(&led3);
               ret = led_turn_off(&led4);
               break;
           case 15:
               ret = led_turn_on(&led1);
               ret = led_turn_on(&led2);
               ret = led_turn_on(&led3);
               ret = led_turn_off(&led4);
               break;               
           case 20:
               ret = led_turn_on(&led1);
               ret = led_turn_on(&led2);
               ret = led_turn_on(&led3);
               ret = led_turn_on(&led4);
               break; */              
                       
       
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


