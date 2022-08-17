/* 
 * File:   euc_DC_motor.c
 * Author: El-Wattaneya
 *
 * Created on 24 ?????, 2022, 07:36 ?
 */

#include "euc_DC_motor.h"
/**
 * 
 * @param _dc_motor
 * @return 
 */



std_returntype dc_motor_intialize(const dc_motor_t * _dc_motor )
{
    std_returntype ret= E_NOT_OK;
        if(NULL==_dc_motor)
            {
                ret=E_NOT_OK;
            }
    
        else
            {
                

                gpio_pin_initailize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
                gpio_pin_initailize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));

            }

    return ret;
}
/**
 * 
 * @param _dc_motor
 * @return 
 */
std_returntype dc_motor_move_right(const dc_motor_t * _dc_motor )
{
    std_returntype ret= E_NOT_OK;
        if(NULL==_dc_motor)
            {
                ret=E_NOT_OK;
            }
    
        else
            {
                gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_HIGH);
                gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);

            }

    return ret;


}
/**
 * 
 * @param _dc_motor
 * @return 
 */
std_returntype dc_motor_move_left(const dc_motor_t * _dc_motor )
{
    std_returntype ret= E_NOT_OK;
        if(NULL==_dc_motor)
            {
                ret=E_NOT_OK;
            }
    
        else
            {
                gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
                gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_HIGH);

            }

    return ret;

}
/**
 * 
 * @param _dc_motor
 * @return 
 */
std_returntype dc_motor_stop(const dc_motor_t * _dc_motor )
{
    std_returntype ret= E_NOT_OK;
        if(NULL==_dc_motor)
            {
                ret=E_NOT_OK;
            }
    
        else
            {
                gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]),GPIO_LOW);
                gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]),GPIO_LOW);

            }

    return ret;


}
