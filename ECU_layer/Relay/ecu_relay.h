/* 
 * File:   ecu_relay.h
 * Author: El-Wattaneya
 *
 * Created on 24 ?????, 2022, 05:20 ?
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*........section include.........*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_relay_cfg.h"


/*........section: macro declarations......... */
#define RELAY_ON_STATUS  0X01U
#define RELAY_OFF_STATUS  0X00U

/*........section: macro function declarations......... */


/*........section: data type declarations......... */
typedef struct{
    uint8 relay_port:4;
    uint8 relay_pin:3;
    uint8 relay_status:1;
}relay_t;

/*........section: function declarations......... */
std_returntype relay_intialize(const relay_t* _relay );
std_returntype relay_turn_on(const relay_t* _relay );
std_returntype relay_turn_off(const relay_t* _relay );

#endif	/* ECU_RELAY_H */

