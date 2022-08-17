/* 
 * File:   hal_timer2.h
 * Author: El-Wattaneya
 *
 * Created on 30 ?????, 2022, 05:16 ?
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/*........section include.........*/
#include "../pic16f877a.h"
#include "../mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*........section: macro declarations......... */ 
#define TIMER2_POSTCALER_DIV_BY_1    0
#define TIMER2_POSTCALER_DIV_BY_2    1
#define TIMER2_POSTCALER_DIV_BY_3    2
#define TIMER2_POSTCALER_DIV_BY_4    3
#define TIMER2_POSTCALER_DIV_BY_5    4
#define TIMER2_POSTCALER_DIV_BY_6    5
#define TIMER2_POSTCALER_DIV_BY_7    6
#define TIMER2_POSTCALER_DIV_BY_8    7
#define TIMER2_POSTCALER_DIV_BY_9    8
#define TIMER2_POSTCALER_DIV_BY_10   9 
#define TIMER2_POSTCALER_DIV_BY_11   10
#define TIMER2_POSTCALER_DIV_BY_12   11
#define TIMER2_POSTCALER_DIV_BY_13   12
#define TIMER2_POSTCALER_DIV_BY_14   13
#define TIMER2_POSTCALER_DIV_BY_15   14
#define TIMER2_POSTCALER_DIV_BY_16   15

#define TIMER2_PRESCALER_DIV_BY_1    0
#define TIMER2_PRESCALER_DIV_BY_4    1
#define TIMER2_PRESCALER_DIV_BY_16   2
/*........section: macro function declarations......... */

#define TIMER2_MODULE_ENABLE()                        (T2CONbits.TMR2ON=1)
#define TIMER2_MODULE_DISABLE()                       (T2CONbits.TMR2ON=0)

#define TIMER2_PRESCALER_SELECT(_PRESCALER_)          (T2CONbits.T2CKPS=_PRESCALER_)

#define TIMER2_POSTCALER_SELECT(_POSTCALER_)          (T2CONbits.TOUTPS=_POSTCALER_)

/*........section: data type declarations......... */



typedef struct {
#if TIMER2_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    void (*TIMER2_InterruptHandler)(void);
#endif 
    uint8 timer2_preload_value;
    uint8 postscaler_value:4;
    uint8 perscaler_value:2;
    uint8 timer2_reserved:2;
}timer2_t;



/*........section: function declarations......... */

std_returntype Timer2_Init(const timer2_t * _timer2);
std_returntype Timer2_DeInit(const timer2_t * _timer2);
std_returntype Timer2_Write_Value(const timer2_t * _timer2,uint8 value);
std_returntype Timer2_Read_Value(const timer2_t * _timer2,uint8* value);

#endif	/* HAL_TIMER2_H */

