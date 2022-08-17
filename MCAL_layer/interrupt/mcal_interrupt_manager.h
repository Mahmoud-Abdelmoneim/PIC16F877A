/* 
 * File:   mcal_interrupt_manager.h
 * Author: El-Wattaneya
 *
 * Created on 26 ?????, 2022, 05:43 ?
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/*........section include.........*/
#include "mcal_interrupt_cfg.h"

/*........section: macro declarations......... */


/*........section: macro function declarations......... */

/*........section: data type declarations......... */

/*........section: function declarations......... */
void INT0_ISR(void);
void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);
void ADC_ISR();
void TIM0_ISR(void);
void TIM1_ISR(void);
void TIM2_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void USART_TX_ISR(void);
void USART_RX_ISR(void);
void SPI_ISR(void);
void I2C_ISR();
void I2C_BC_ISR();
#endif	/* MCAL_INTERRUPT_MANAGER_H */

