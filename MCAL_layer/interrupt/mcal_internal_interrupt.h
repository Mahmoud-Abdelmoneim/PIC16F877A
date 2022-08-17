/* 
 * File:   mcal_internal_interrupt.h
 * Author: El-Wattaneya
 *
 * Created on 26 ?????, 2022, 05:40 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/*........section include.........*/
#include "mcal_interrupt_cfg.h"
/*........section: macro declarations......... */\
/*===============Analog To Digital Converter====================*/
/*=============================================================*/
#if ADC_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define ADC__InterruptDisable()             (PIE1bits.ADIE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define ADC_InterrupEnable()                (PIE1bits.ADIE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define ADC_InterruptFlagClear()            (PIR1bits.ADIF=0)     
#endif

/*====================Timer0 Interrupt==========================*/
/*=============================================================*/
#if TIMER0_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define TIMER0_InterruptDisable()              (INTCONbits.T0IE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define TIMER0_InterrupEnable()                (INTCONbits.T0IE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define TIMER0_InterruptFlagClear()            (INTCONbits.T0IF=0)     
#endif
/*====================Timer1 Interrupt==========================*/
/*=============================================================*/
#if TIMER1_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define TIMER1_InterruptDisable()              (PIE1bits.TMR1IE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define TIMER1_InterrupEnable()                (PIE1bits.TMR1IE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define TIMER1_InterruptFlagClear()            (PIR1bits.TMR1IF=0)     
#endif
/*====================Timer2 Interrupt==========================*/
/*=============================================================*/
#if TIMER2_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define TIMER2_InterruptDisable()              (PIE1bits.TMR2IE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define TIMER2_InterrupEnable()                (PIE1bits.TMR2IE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define TIMER2_InterruptFlagClear()            (PIR1bits.TMR2IF=0) 
#endif
/*====================CCP Interrupt==========================*/
/*=============================================================*/
#if CCP1_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define CCP1_InterruptDisable()              (PIE1bits.CCP1IE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define CCP1_InterrupEnable()                (PIE1bits.CCP1IE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define CCP1_InterruptFlagClear()            (PIR1bits.CCP1IF=0) 
#endif
#if CCP2_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define CCP2_InterruptDisable()              (PIE2bits.CCP2IE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define CCP2_InterrupEnable()                (PIE2bits.CCP2IE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define CCP2_InterruptFlagClear()            (PIR2bits.CCP2IF=0) 
#endif

/*====================USART Interrupt==========================*/
/*=============================================================*/
#if USART_TX_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define USART_TX_InterruptDisable()              (PIE1bits.TXIE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define USART_TX_InterrupEnable()                (PIE1bits.TXIE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define USART_TX_InterruptFlagClear()            (PIR1bits.TXIF=0) 
#endif

#if USART_RX_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define USART_RX_InterruptDisable()              (PIE1bits.RCIE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define USART_RX_InterrupEnable()                (PIE1bits.RCIE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define USART_RX_InterruptFlagClear()            (PIR1bits.RCIF=0) 
#endif

/*====================SPI Interrupt==========================*/
/*=============================================================*/
#if SPI_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define SPI_InterruptDisable()              (PIE1bits.SSPIE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define SPI_InterrupEnable()                (PIE1bits.SSPIE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define SPI_InterruptFlagClear()            (PIR1bits.SSPIF=0) 
#endif

/*====================I2C Interrupt==========================*/
/*=============================================================*/
#if MSSP_I2C_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
/* .......this routine clear the interrupt enable bit for ADC module....  */
#define MSSP_I2C_InterruptDisable()              (PIE1bits.SSPIE=0)
#define MSSP_I2C_BUS_COL_InterruptDisable()      (PIE2bits.BCLIE=0)
/* .......this routine set the interrupt enable bit for ADC module....  */
#define MSSP_I2C_InterrupEnable()                (PIE1bits.SSPIE=1)
#define MSSP_I2C_BUS_COL_InterruptDEnable()      (PIE2bits.BCLIE=1)
/*........this routine clear bit for interrupt flag for ADC module....*/
#define MSSP_I2C_InterruptFlagClear()            (PIR1bits.SSPIF=0) 
#define MSSP_I2C_BUS_COL_InterruptFlagClear()    (PIR2bits.BCLIF=0) 
#endif
/*........section: macro function declarations......... */

/*........section: data type declarations......... */
typedef void (*interruptHandler)(void);
/*........section: function declarations......... */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

