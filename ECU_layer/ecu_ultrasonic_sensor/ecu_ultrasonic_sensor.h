/* 
 * File:   ecu_ultrasonic_sensor.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 17 , 2022, 03:41 
 */

#ifndef ECU_ULTRASONIC_SENSOR_H
#define	ECU_ULTRASONIC_SENSOR_H

/*........section include.........*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/Timer1/hal_timer1.h"

/*........section: macro declarations......... */


/*........section: macro function declarations......... */


/*........section: data type declarations......... */
typedef struct{
    pin_config_t trigger; //trigger initialize as output
    pin_config_t echo;    //echo initialize as input
}ultrasonic_t;

/*........section: function declarations......... */
std_returntype Ultrasonic_Init(const ultrasonic_t *_ultasonic);
std_returntype Ultrasonic_calculate_Distance(const ultrasonic_t *_ultasonic,uint16 * _distance);

#endif	/* ECU_ULTRASONIC_SENSOR_H */

