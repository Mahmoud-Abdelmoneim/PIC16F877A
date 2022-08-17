/* 
 * File:   application.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 03:38 ?
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
#include "ECU_layer/LED/ecu_led.h"
#include "ECU_layer/button/euc_button.h"
#include "ECU_layer/Relay/ecu_relay.h"
#include "ECU_layer/DC Motor/euc_DC_motor.h"
#include "ECU_layer/ecu_seven_seg/ecu_seven_seg.h"
#define _XTAL_FREQ 4000000


/*........section: function declarations......... */
void application_intialize(void);


#endif	/* APPLICATION_H */

