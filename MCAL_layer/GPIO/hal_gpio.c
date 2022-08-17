#include "hal_gpio.h"
/*.........defintion of TRIS register............*/
volatile uint8 * tris_register[]={&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/*.........defintion of PORT register............*/
volatile uint8 * port_register[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

/**
 *
 * @param _pin_config:pointer to configuration
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_pin_diriction_initailize(const pin_config_t * _pin_config)
{
    std_returntype ret=E_OK;
    
    if(NULL==_pin_config)
        ret=E_NOT_OK;
    else
    {
        switch(_pin_config->direction)
                {
                    case GPIO_DIRICTION_OUTPUT:
                        CLEAR_BIT(*tris_register[_pin_config->port],_pin_config->pin);
                        break;
                    case GPIO_DIRICTION_INPUT:
                        SET_BIT(*tris_register[_pin_config->port],_pin_config->pin);
                        break;
                    default: ret=E_NOT_OK;   
                }  
    }
    return ret;
}
#endif
/**
 * 
 * @param _pin_config:pointer to configuration
 * @param dic_status
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_pin_get_diriction(const pin_config_t * _pin_config,direction_t * dic_status)
{
    std_returntype ret=E_OK;
     if(NULL==_pin_config || NULL==dic_status)
        ret=E_NOT_OK;
     else
     {
         * dic_status= READ_BIT(*tris_register [_pin_config->port],_pin_config->pin);       
     }
    
    return ret;
}
#endif
/**
 * 
 * @param _pin_config:pointer to configuration
 * @param logic
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_pin_write_logic(const pin_config_t * _pin_config,logic_t logic)
{
    std_returntype ret=E_OK;
    if(NULL==_pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
        ret=E_NOT_OK;
    else
    {
        switch(logic)
           {
                case GPIO_HIGH:
                   SET_BIT(*port_register[_pin_config->port],_pin_config->pin);
                   
                   break;
                case GPIO_LOW:
                   CLEAR_BIT(*port_register[_pin_config->port],_pin_config->pin);
                   break; 
                default: ret=E_NOT_OK;     
           }
    
    }
      
    return ret;
}
#endif
/**
 * 
 * @param _pin_config:pointer to configuration
 * @param logic
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_pin_read_logic(const pin_config_t * _pin_config,logic_t * logic)
{
    std_returntype ret=E_OK;
    if(NULL==_pin_config || NULL==logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1)
        ret=E_NOT_OK;
     else
     {
        *logic = READ_BIT(*port_register[_pin_config->port], _pin_config->pin);
     }
    
    return ret;
}
#endif
/**
 * 
 * @param _pin_config:pointer to configuration
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action     
 */
#if GPIO_PORT_PIN_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_pin_toggle_logic(const pin_config_t * _pin_config)
{
    std_returntype ret=E_OK;
    if(NULL==_pin_config)
        ret=E_NOT_OK;
    else
    {
        TOGGLE_BIT(*port_register[_pin_config->port],_pin_config->pin);
    }
    
    return ret;
}
#endif
/**
 * 
 * @param _pin_config:pointer to configuration 
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_pin_initailize(const pin_config_t * _pin_config)
{
     std_returntype ret=E_OK;
    if(NULL==_pin_config)
        ret=E_NOT_OK;
    else
    {
       ret= gpio_pin_diriction_initailize(_pin_config);
       ret= gpio_pin_write_logic(_pin_config,_pin_config->logic);
    }
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param dirction
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */
#if GPIO_PORT_CONFIGURATION == GONFIG_ENABLE 
std_returntype gpio_port_diriction_initailize(port_index_t port,uint8 dirction)
{
    std_returntype ret=E_OK;
    if(port > PORT_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
        *tris_register [port] = dirction;
        
    }
    return ret;

}
#endif
/**
 * 
 * @param port
 * @param direction_status
 * @return:status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action 
 */
#if GPIO_PORT_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_port_get_diriction(port_index_t port,uint8 * direction_status)
{
    std_returntype ret=E_OK;
    if((NULL==direction_status) || (port > PORT_MAX_NUMBER-1))
        ret=E_NOT_OK;
    else
    {
        * direction_status = *tris_register [port];  
    
    }
    
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return :status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action
 */

#if GPIO_PORT_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_port_write_logic(port_index_t port,uint8 logic)
{
    std_returntype ret=E_OK;
     if(port > PORT_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
       *port_register[port] = logic; 
    
    }
    
    return ret;
}
#endif
/**
 * 
 * @param port
 * @param logic
 * @return :status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_port_read_logic(port_index_t port,uint8 * logic)
{
    std_returntype ret=E_OK;
    if((NULL==logic) && (port > PORT_MAX_NUMBER-1))
        ret=E_NOT_OK;
    else
    {
       * logic = *port_register[port];
    }
    
    return ret;
}
#endif

/**
 * 
 * @param port
 * @return :status of the function 
 *        (E_OK)    : the function done successfully 
 *        (E_NOT_OK): the function has issue to perform this action
 */
#if GPIO_PORT_CONFIGURATION == GONFIG_ENABLE
std_returntype gpio_port_toggle_logic(port_index_t port)
{
    std_returntype ret=E_OK;
      if(port > PORT_MAX_NUMBER-1)
    {
        ret=E_NOT_OK;
    }
    else
    {
       *port_register[port] ^=  PORT_MASK; 
    
    }
    
    return ret;

}
#endif