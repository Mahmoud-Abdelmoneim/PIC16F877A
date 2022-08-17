/* 
 * File:   ecu_keypad.h
 * Author:Mahmoud Abdelmoniem
 *
 * Created on 25 , 2022, 08:16 
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*........section: includes......... */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"



/*........section: macro declarations......... */
#define ECU_KEYPAD_ROWS        4
#define ECU_KEYPAD_COLUMNS     4


/*........section: data type declarations......... */

typedef struct {
    pin_config_t keypad_row_pin[ECU_KEYPAD_ROWS];
    pin_config_t keypad_column_pin[ECU_KEYPAD_ROWS];
            
}keypad_t;
/*........section: macro function declarations......... */



/*........section: function declarations......... */

std_returntype keypad_intialize(const keypad_t* _keypad);
std_returntype keypad_get_value(const keypad_t* _keypad,uint8 * value);





#endif	/* ECU_KEYPAD_H */

