/* 
 * File:   euc_DC_motor.h
 * Author: El-Wattaneya
 *
 * Created on 24 ?????, 2022, 07:36 ?
 */

#ifndef EUC_DC_MOTOR_H
#define	EUC_DC_MOTOR_H

/*.........section: includes.............*/

#include "euc_DCmotor_cfg.h"
#include "../../MCAL_layer/../MCAL_layer/GPIO/hal_gpio.h"

/*........section: macro declarations......... */
#define DC_MOTOR_ON_STATUS   0X01U
#define DC_MOTOR_OFF_STATUS  0X00U
 
#define DC_MOTOR_PIN1        0X00U 
#define DC_MOTOR_PIN2        0X01U
/*........section: macro function declarations......... */


/*........section: data type declarations......... */

typedef struct
{
    pin_config_t dc_motor_pin[2];

}dc_motor_t;

/*........section: function declarations......... */
std_returntype dc_motor_intialize(const dc_motor_t * _dc_motor );
std_returntype dc_motor_move_right(const dc_motor_t * _dc_motor );
std_returntype dc_motor_move_left(const dc_motor_t * _dc_motor );
std_returntype dc_motor_stop(const dc_motor_t * _dc_motor );
#endif	/* EUC_DC_MOTOR_H */

