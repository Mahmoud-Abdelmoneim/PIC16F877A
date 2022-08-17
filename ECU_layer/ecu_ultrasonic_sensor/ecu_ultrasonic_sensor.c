#include "ecu_ultrasonic_sensor.h"
timer1_t timr1={
  
  .perscaler_value = TIMER1_PRESCALER_DIV_BY_1,
  .timer1_mode = TIMER1_TIMER_MODE,
  .timer1_osc_cfg = RIMER1_OCS_DISABLE,
  .timer1_preload_value = 0  
};
timer1_t timr1;
std_returntype Ultrasonic_Init(const ultrasonic_t *_ultasonic){
    std_returntype ret=E_OK;
    
    if(NULL==_ultasonic)
        ret=E_NOT_OK;
    else
    {
        //set trigger and echo pins
        ret = gpio_pin_initailize(&(_ultasonic->trigger));
        
        ret = gpio_pin_initailize(&(_ultasonic->echo));
            
    }
    return ret;    
}
std_returntype Ultrasonic_calculate_Distance(const ultrasonic_t *_ultasonic,uint16 * _distance){
    std_returntype ret=E_OK;
    logic_t stat=GPIO_LOW;
    if(NULL==_ultasonic)
        ret=E_NOT_OK;
    else
    {
            
        
        ret = Timer1_Write_Value(&timr1,0);
        // Send Trigger Pulse To The Sensor
        ret = gpio_pin_write_logic(&(_ultasonic->trigger),GPIO_HIGH);
        __delay_us(10);
        ret = gpio_pin_write_logic(&(_ultasonic->trigger),GPIO_LOW);
        
        // Wait For The Echo Pulse From The Sensor
        
        while(stat==GPIO_LOW){
            ret = gpio_pin_read_logic(&(_ultasonic->echo),&stat);
        }
        // Turn ON Timer Module
        
        ret = Timer1_Init(&timr1);
        // Wait Until The Pulse Ends
        while(stat==GPIO_HIGH){
            ret = gpio_pin_read_logic(&(_ultasonic->echo),&stat);
        }
        // Turn OFF The Timer
        
        ret = Timer1_DeInit(&timr1);
        // Calculate The Distance Using The Equation
        *_distance=TMR1/58.82;
        
    }
    return ret;    
}