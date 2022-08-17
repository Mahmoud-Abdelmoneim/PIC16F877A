/* 
 * File:   ecu_seven_seg.h
 * Author: El-Wattaneya
 *
 * Created on 25 ?????, 2022, 03:24 ?
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/*.........section: includes.............*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*........section: macro function declarations......... */
#define SEEGMENT_PIN0  0
#define SEEGMENT_PIN1  1
#define SEEGMENT_PIN2  2
#define SEEGMENT_PIN3  3

/*........section: data type declarations......... */
typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE        
}segment_type_t;

typedef struct
{
    pin_config_t  segment_pin[4];
    segment_type_t segment_type;
}segment_t;


/*........section: function declarations......... */
std_returntype seven_seg_intialize(const segment_t* _segment );
std_returntype seven_seg_write_number(const segment_t* _segment ,uint8 number);

#endif	/* ECU_SEVEN_SEG_H */

