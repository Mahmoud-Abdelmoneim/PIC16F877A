/* 
 * File:   application.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 03:38 ?
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
#include "ECU_layer/ecu_layer_init/ecu_layer_init.h" 
#include "MCAL_layer/interrupt/mcal_external_interrupt.h"



extern keypad_t keypad1;


/*........section: function declarations......... */
void application_intialize(void);


#endif	/* APPLICATION_H */

