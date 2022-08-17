/* 
 * File:   ecu_seven_seg.c
 * Author: El-Wattaneya
 *
 * Created on 25 ?????, 2022, 03:24 ?
 */

#include "ecu_seven_seg.h"

/**
 * This Interface to make the needed GPIO and segment initialization
 * @param seg pointer to the segment configurations 
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_returntype seven_seg_intialize(const segment_t* _segment )
{
    std_returntype ret= E_NOT_OK;
        if(NULL==_segment)
            {
                ret=E_NOT_OK;
            }
        else 
            {
                gpio_pin_initailize(&(_segment->segment_pin[SEEGMENT_PIN0]));
                gpio_pin_initailize(&(_segment->segment_pin[SEEGMENT_PIN1]));
                gpio_pin_initailize(&(_segment->segment_pin[SEEGMENT_PIN2]));
                gpio_pin_initailize(&(_segment->segment_pin[SEEGMENT_PIN3]));

            }

    return ret;

}
/**
 * Write a number to the segment 0 ~ 9
 * @param seg pointer to the segment configurations 
 * @param number the needed number to show
 * @return  Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue while performing this action
 */
std_returntype seven_seg_write_number(const segment_t* _segment ,uint8 number)
{
    std_returntype ret= E_NOT_OK;
        if(NULL==_segment && number>9)
            {
                ret=E_NOT_OK;
            }
        else 
            {
                gpio_pin_write_logic(&(_segment->segment_pin[SEEGMENT_PIN0]),(number>>0) & 0x01);
                gpio_pin_write_logic(&(_segment->segment_pin[SEEGMENT_PIN1]),(number>>1) & 0x01);                
                gpio_pin_write_logic(&(_segment->segment_pin[SEEGMENT_PIN2]),(number>>2) & 0x01);
                gpio_pin_write_logic(&(_segment->segment_pin[SEEGMENT_PIN3]),(number>>3) & 0x01);

            }

    return ret;


}
