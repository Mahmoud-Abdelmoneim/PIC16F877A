/* 
 * File:   mcal_external_interrupt.h
 * Author: El-Wattaneya
 *
 * Created on 26 ?????, 2022, 05:41 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H


/*........section include.........*/
#include "mcal_interrupt_cfg.h"
/*........section: macro declarations......... */
#if EXTERNAL_INTERRUPT_INT0_FEATIRE_ENABLE  ==  INTERRUPT_FEATIRE_ENABLE
/* .......this routine set the interrupt enable bit for INT0....  */
#define EXT_INT0_InterrupEnable()               (INTCONbits.INTE=1)
/* .......this routine clear the interrupt enable bit for INT0....  */
#define EXT_INT0_InterruptDisable()             (INTCONbits.INTE=0)
/*........this routine clear bit for interrupt flag the external INT0....*/
#define EXT_INT0_InterruptFlagClear()           (INTCONbits.INTF=0)
/*........this routine set the edge detect for external interrupt positive edge */
#define EXT_INT0_RisingEdgeSet()                (OPTION_REGbits.INTEDG=1)
/*........this routine set the edge detect for external interrupt negative edge */
#define EXT_INT0_FallingEdgeSet()               (OPTION_REGbits.INTEDG=0)
#endif
#if EXTERNAL_INTERRUPT_PORTB_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
/* .......this routine set the interrupt enable bit for RORTB....  */
#define EXT_RORTB_InterruptEnable()             (INTCONbits.RBIE=1)
/* .......this routine clear the interrupt enable bit for RORTB....  */
#define EXT_RORTB_InterruptDisable()            (INTCONbits.RBIE=0)
/*........this routine clear bit for interrupt flag the external RORTB....*/
#define EXT_RORTB_InterruptFlagClear()          (INTCONbits.RBIF=0)



#endif



/*........section: macro function declarations......... */

/*........section: data type declarations......... */
typedef void (*InterruptHandler)(void);
typedef enum{

    INTERRUPT_FALLING_EDGE =0,
    INTERRUPT_RISING_EDGE

}Interrupt_INTx_edge;

typedef enum{

    INTERRUPT_EXTERNAL_INT0 =0,

}Interrupt_INTx_sc;

typedef struct {
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    Interrupt_INTx_edge edge;
    Interrupt_INTx_sc source;
}inteerrupt_INTx_t;
typedef struct {
    void (* EXT_InterruptHandler_HIGH)(void);
    void (* EXT_InterruptHandler_LOW)(void);
    pin_config_t mcu_pin;

}inteerrupt_RBx_t;
/*........section: function declarations......... */

/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_INT0_Init(const inteerrupt_INTx_t* int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_INT0_DeInit(const inteerrupt_INTx_t* int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_RBx_Init(const inteerrupt_RBx_t* int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_RBx_DeInit(const inteerrupt_RBx_t* int_obj);
#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

