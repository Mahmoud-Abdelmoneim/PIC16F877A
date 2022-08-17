#include "ecu_relay.h"



/**
 * 
 * @param _relay
 * @return 
 */
std_returntype relay_intialize(const relay_t* _relay )
{
        std_returntype ret= E_NOT_OK;
        if(NULL==_relay)
            {
                ret=E_NOT_OK;
            }
        else
            {
                pin_config_t pin_obj={.port=_relay->relay_port,.pin=_relay->relay_pin,.logic=_relay->relay_status
                                       ,.direction=GPIO_DIRICTION_OUTPUT};
                gpio_pin_initailize(&pin_obj);
            }
        
        return ret;

}
/**
 * 
 * @param _relay
 * @return 
 */
std_returntype relay_turn_on(const relay_t* _relay )
{
        std_returntype ret= E_NOT_OK;
        if(NULL==_relay)
            {
                ret=E_NOT_OK;
            }
        else
            {
                pin_config_t pin_obj={.port=_relay->relay_port,.pin=_relay->relay_pin,.logic=_relay->relay_status
                                       ,.direction=GPIO_DIRICTION_OUTPUT};
                gpio_pin_write_logic(&pin_obj,GPIO_HIGH);
                
            }
        return ret;

}
/**
 * 
 * @param _relay
 * @return 
 */
std_returntype relay_turn_off(const relay_t* _relay )
{
        std_returntype ret= E_NOT_OK;
        if(NULL==_relay)
            {
                ret=E_NOT_OK;
            }
        else
            {
                pin_config_t pin_obj={.port=_relay->relay_port,.pin=_relay->relay_pin,.logic=_relay->relay_status
                                       ,.direction=GPIO_DIRICTION_OUTPUT};
                gpio_pin_write_logic(&pin_obj,GPIO_LOW);
            }
        
        return ret;

}
