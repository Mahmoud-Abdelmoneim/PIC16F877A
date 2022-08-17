#include "euc_button.h"



/**
 * @brief Initialize the assigned pin to be Input.
 * @param btn pointer to the button configurations
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_returntype button_intialize(const button_t * btn)
{        
      std_returntype ret= E_OK;
    if(NULL==btn)
    {
        ret=E_NOT_OK;
    }
    else
    {
      ret =gpio_pin_diriction_initailize(&(btn->button_pin));
        
    }   
    return ret;

}
/**
 * @brief Read the state of the button
 * @param btn pointer to the button configurations
 * @param btn_state button state @ref button_state_t
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_returntype read_button_state(const button_t * btn,botton_state_t *btn_state)
{
       std_returntype ret= E_NOT_OK;
       
       logic_t Pin_Logic_Status =GPIO_LOW;
    if(NULL==btn || NULL== btn_state)
    {
        ret=E_NOT_OK;
    }
   else{
        gpio_pin_read_logic(&(btn->button_pin), &Pin_Logic_Status);
        switch(btn->button_connection){
            case BUTTON_ACTIVE_HIGH:
            {
                    if(GPIO_HIGH == Pin_Logic_Status){
                        *btn_state = BUTTON_PRESSED;
                    }
                    else{
                        *btn_state = BUTTON_RELEASED;
                    }
            break;
            }
        
            case BUTTON_ACTIVE_LOW:
                    {
                    if(GPIO_HIGH == Pin_Logic_Status){
                        *btn_state = BUTTON_RELEASED;
                    }
                    else{
                        *btn_state = BUTTON_PRESSED;
                    }
                    break;
                    }
            default: ;
            
        ret = E_OK;
    }
    
}
       return ret;
}

