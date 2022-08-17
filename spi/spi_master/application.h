/* 
 * File:   application.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 03:38 ?
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
#include "ECU_layer/button/euc_button.h"
#include "ECU_layer/ecu_layer_init/ecu_layer_init.h" 
#include "MCAL_layer/interrupt/mcal_external_interrupt.h"
#include "MCAL_layer/ADC/hal_adc.h"
#include "MCAL_layer/Timer0/hal_timer0.h"
#include "MCAL_layer/Timer1/hal_timer1.h"
#include "MCAL_layer/Timer2/hal_timer2.h"
#include "MCAL_layer/CCP/hal_ccp.h" 
#include "MCAL_layer/usart/hal_usart.h"
#include "MCAL_layer/SPI/hal_spi.h"
#include "MCAL_layer/I2C/hal_i2c.h"



/*........section: function declarations......... */
void application_intialize(void);


#endif	/* APPLICATION_H */

