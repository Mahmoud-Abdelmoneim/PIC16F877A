/* 
 * File:   mcal_interrupt_cfg.h
 * Author: El-Wattaneya
 *
 * Created on 26 ?????, 2022, 05:39 ?
 */

#ifndef MCAL_INTERRUPT_CFG_H
#define	MCAL_INTERRUPT_CFG_H

/*........section include.........*/
#include "../pic16f877a.h"
#include "../mcal_std_types.h"
#include "mcal_intrrupt_gen_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*........section: macro declarations......... */
#define INTERRUPT_ENABLE           1
#define INTERRUPT_DISENABLE        0

#define INTERRUPT_OCCUR            1
#define INTERRUPT_NOT_OCCUR        0

/*........section: macro function declarations......... */


/*this macro set global interrupt enable */ 
#define INTERRUPT_Golableinterruptenable()          (INTCONbits.GIE=1)

/*this macro reset global interrupt enable */
#define INTERRUPT_Golableinterruptdisable()         (INTCONbits.GIE=0)

/*this macro set peripheral interrupt enable */
#define INTERRUPT_peripheralinterruptenable()       (INTCONbits.PEIE=1)

/*this macro reset peripheral interrupt enable */
#define INTERRUPT_peripheralinterruptdisable()      (INTCONbits.PEIE=0)
/*........section: data type declarations......... */

/*........section: function declarations......... */

#endif	/* MCAL_INTERRUPT_CFG_H */

