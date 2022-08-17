/* 
 * File:   hal_timer1.h
 * Author: El-Wattaneya
 *
 * Created on 30 ?????, 2022, 10:22 ?
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H
/*........section include.........*/
#include "../pic16f877a.h"
#include "../mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../..//MCAL_layer/interrupt/mcal_internal_interrupt.h"
/*........section: macro function declarations......... */
#define TIMER1_COUNTER_MODE          1
#define TIMER1_TIMER_MODE            0

#define TIMER1_SYN_COUNTER_MODE      0
#define TIMER1_ASYN_COUNTER_MODE     1

#define RIMER1_OCS_ENABLE            1
#define RIMER1_OCS_DISABLE           0

#define TIMER1_PRESCALER_DIV_BY_1    0
#define TIMER1_PRESCALER_DIV_BY_2    1
#define TIMER1_PRESCALER_DIV_BY_4    2
#define TIMER1_PRESCALER_DIV_BY_8    3



/*........section: data type declarations......... */
#define TIMER1_PERSCALER_ENABLE()                     (OPTION_REGbits.PSA=0)
#define TIMER1_PERSCALER_DISABLE()                    (OPTION_REGbits.PSA=1)

#define TIMER1_MODULE_ENABLE()                        (T1CONbits.TMR1ON=1)
#define TIMER1_MODULE_DISABLE()                       (T1CONbits.TMR1ON=0)

#define TIMER1_SELECT_TIMER_MODE()                    (T1CONbits.TMR1CS=0)
#define TIMER1_SELECT_COUNTER_MODE()                  (T1CONbits.TMR1CS=1)

#define TIMER1_ASYN_COUNTER_MODE_ENABLE()                    (T1CONbits.T1SYNC=1)
#define TIMER1_SYN_COUNTER_MODE_ENABLE()                     (T1CONbits.T1SYNC=0)

#define TIMER1_OSC_HW_ENABLE()                        (T1CONbits.T1OSCEN=1)
#define TIMER1_OSC_HW_DISABLE()                       (T1CONbits.T1OSCEN=0)

#define TIMER1_PRESCALER_SELECT(_PRESCALER_)          (T1CONbits.T1CKPS=_PRESCALER_)

/*........section: macro declarations......... */ 

typedef struct {
#if TIMER1_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    void (*TIMER1_InterruptHandler)(void);
#endif 
    uint8 perscaler_value:2;
    uint16 timer1_preload_value;
    uint8 timer1_mode:1;
    uint8 timer1_counter_syn_mode:1;
    uint8 timer1_osc_cfg:1;
    uint8 timer1_reserved:3;


}timer1_t;
/*........section: function declarations......... */
std_returntype Timer1_Init(const timer1_t * _timer1);
std_returntype Timer1_DeInit(const timer1_t * _timer1);
std_returntype Timer1_Write_Value(const timer1_t * _timer1,uint16 value);
std_returntype Timer1_Read_Value(const timer1_t * _timer1,uint16* value);
#endif	/* HAL_TIMER1_H */

