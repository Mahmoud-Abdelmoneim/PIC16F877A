/* 
 * File:   ecu_led.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 , 2022, 03:35 
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/*........section include.........*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h" 

/*........section: macro declarations......... */



/*........section: macro function declarations......... */


/*........section: data type declarations......... */
typedef enum {
    LED_OFF,
    LED_ON        
}led_status_t;

typedef struct {
    uint8 port_name:4;
    uint8 pin:3;
    uint8 led_status:1;
}led_t;


/*........section: function declarations......... */
std_returntype led_intialize(const led_t *led );
std_returntype led_turn_on(const led_t *led);
std_returntype led_turn_off(const led_t *led);
std_returntype led_turn_toggle(const led_t *led);
#endif	/* ECU_LED_H */

