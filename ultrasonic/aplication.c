/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
#include "ECU_layer/ecu_ultrasonic_sensor/ecu_ultrasonic_sensor.h"
std_returntype ret = E_OK;
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
uint8 distance=0;
int main(){
    ret = Ultrasonic_Init(&ultrasonic);
    while(1){
        ret = Ultrasonic_calculate_Distance(&ultrasonic,&distance);
    }
    
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


