/* 
 * File:   euc_button.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 17 , 2022, 08:28 
 */

#ifndef EUC_BUTTON_H
#define	EUC_BUTTON_H
/*........section include.........*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_button_cfg.h"

/*........section: macro declarations......... */



/*........section: macro function declarations......... */


/*........section: data type declarations......... */
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED        
}botton_state_t;

typedef enum
{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}botton_active;

typedef struct
{
    pin_config_t button_pin;
    botton_state_t button_state;
    botton_active button_connection;
    
}button_t;


/*........section: function declarations......... */
std_returntype button_intialize(const button_t * btn);
std_returntype read_button_state(const button_t * btn,botton_state_t *btn_state);

#endif	/* EUC_BUTTON_H */

