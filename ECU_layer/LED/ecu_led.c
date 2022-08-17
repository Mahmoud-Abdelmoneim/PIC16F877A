#include "ecu_led.h"

 
/**
 * 
 * @param led:pointer to led module configuration
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action  
 */

std_returntype led_intialize(const led_t *led )
{
    std_returntype ret= E_OK;
    if(NULL==led)
    {
        ret=E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj={.port=led->port_name,.pin=led->pin,
                              .logic=led->led_status,.direction=GPIO_DIRICTION_OUTPUT}; 
        gpio_pin_initailize(&pin_obj);  
        
    }   
    return ret;
}
/**
 * 
 * @param led:pointer to led module configuration
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */
std_returntype led_turn_on(const led_t *led)
{
    std_returntype ret=E_OK;
     if(NULL==led)
    {
        ret=E_NOT_OK;
    }
    else
    {
          pin_config_t pin_obj={.port=led->port_name,.pin=led->pin,
                                .logic=led->led_status,.direction=GPIO_DIRICTION_OUTPUT};
          gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
        
    }
     
     
    return ret;

}
/**
 * 
 * @param led:pointer to led module configuration
 * @return :status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action
 */

std_returntype led_turn_off(const led_t *led)
{
    std_returntype ret=E_OK;
    if(NULL==led)
    {
        ret=E_NOT_OK;
    }
    else
    {
        pin_config_t pin_obj={.port=led->port_name,.pin=led->pin,
                              .logic=led->led_status,.direction=GPIO_DIRICTION_OUTPUT};
          gpio_pin_write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @param led:pointer to led module configuration
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */

std_returntype led_turn_toggle(const led_t *led)
{
    std_returntype ret=E_OK;
     if(NULL==led)
    {
        ret=E_NOT_OK;
    }
    else
    {
          pin_config_t pin_obj={.port=led->port_name,.pin=led->pin,
                              .logic=led->led_status,.direction=GPIO_DIRICTION_OUTPUT};
          gpio_pin_toggle_logic(&pin_obj);
        
    }
     
     
    return ret;
}
