/* 
 * File:   hal_timer0.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 29, 2022, 01:48 
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/*........section include.........*/
#include "../pic16f877a.h"
#include "../mcal_std_types.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
#include "../..//MCAL_layer/GPIO/hal_gpio.h"

/*........section: macro declarations......... */
#define TIMER0_PERSCALER_ENABLE_CFG    1
#define TIMER0_PERSCALER_DISABLE_CFG   0

#define TIMER0_RISING_EDGE    1
#define TIMER0_FALLING_EDGE   0

#define TIMER0_TIMER_MODE      1
#define TIMER0_COUNTER_MODE    0
/*........section: macro function declarations......... */
#define TIMER0_PERSCALER_ENABLE()           (OPTION_REGbits.PSA=0)
#define TIMER0_PERSCALER_DISABLE()          (OPTION_REGbits.PSA=1)

#define TIMER0_RISING_EDGE_ENABLE()         (OPTION_REGbits.T0SE=0)
#define TIMER0_FALLING_EDGE_ENABLE()        (OPTION_REGbits.T0SE=1)

#define TIMER0_SELECT_TIMER_MODE()                 (OPTION_REGbits.T0CS=0)
#define TIMER0_SELECT_COUNTER_MODE()               (OPTION_REGbits.T0CS=1)
/*........section: data type declarations......... */
typedef enum{
    TIM0_PRESCALER_DIV_2=0,
    TIM0_PRESCALER_DIV_4,
    TIM0_PRESCALER_DIV_8,
    TIM0_PRESCALER_DIV_16,
    TIM0_PRESCALER_DIV_32,
    TIM0_PRESCALER_DIV_64,
    TIM0_PRESCALER_DIV_128, 
    TIM0_PRESCALER_DIV_256        
}timer0_prescaler_select_t;

typedef struct{
    void (*Timer0_InterruptHandler)(void);
    timer0_prescaler_select_t prescaler_value;
    uint8 timer0_mode:1;
    uint8 timer0_preload_value;
    uint8 perscaler_enable:1;
    uint8 timer0_counter_edge:1 ;
    
    uint8 timer0_reserved:5;

}timer0_t;
/*........section: function declarations......... */
std_returntype Timer0_Init(const timer0_t * _timer0);
std_returntype Timer0_DeInit(const timer0_t * _timer0);
std_returntype Timer0_Write_Value(const timer0_t * _timer0,uint8 value);
std_returntype Timer0_Read_Value(const timer0_t * _timer0,uint8* value);

#endif	/* HAL_TIMER0_H */

