/* 
 * File:   hal_usart.h
 * Author: El-Wattaneya
 *
 * Created on 04 ?????, 2022, 12:59 ?
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/*........section include.........*/
#include "../pic16f877a.h"
#include "../mcal_std_types.h"
#include "hal_usart_cfg.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*........section: macro declarations......... */
#define USART_MODULE_ENABLE                          1
#define USART_MODULE_DISABLE                         0

#define USART_ASYNCHRONOUS_MODE                      0
#define USART_SYNCHRONOUS_MODE                       1

#define USART_ASYNCHRONOUS_HIGH_SPEED                1
#define USART_ASYNCHRONOUS_LOW_SPEED                  0

#define USART_ASYNCHRONOUS_TX_ENABLE                 1
#define USART_ASYNCHRONOUS_TX_DISABLE                 0

#define USART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE       1
#define USART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE       0

#define USART_ASYNCHRONOUS_TX_9Bit_ENABLE            1
#define USART_ASYNCHRONOUS_TX_9Bit_DISABLE            0

#define USART_ASYNCHRONOUS_RX_ENABLE                 1
#define USART_ASYNCHRONOUS_RX_DISABLE                 0

#define USART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE       1
#define USART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE       0

#define USART_ASYNCHRONOUS_RX_9Bit_ENABLE            1
#define USART_ASYNCHRONOUS_RX_9Bit_DISABLE            0

#define USART_ASYNCHRONOUS_FRAMING_ERROR_DETECT      1
#define USART_ASYNCHRONOUS_FRAMING_ERROR_CLEARED      0

#define USART_ASYNCHRONOUS_OVERRUN_ERROR_DETECT      1
#define USART_ASYNCHRONOUS_OVERRUN_ERROR_CLEARED      0
/*........section: macro function declarations......... */


/*........section: data type declarations......... */
typedef struct{
    uint8 usart_tx_resrved:5;
    uint8 usart_tx_enable:1;
    uint8 usart_tx_interrupt_enable:1;
    uint8 usart_tx_9bit_enable:1;
    
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_rx_resrved:5;
    uint8 usart_rx_enable:1;
    uint8 usart_rx_interrupt_enable:1;
    uint8 usart_rx_9bit_enable:1;
    
}usart_rx_cfg_t;

typedef union{
    struct{
        uint8 usart_tx_resrved:6;
        uint8 usart_ferr:1;
        uint8 usart_oerr:1;
    };
    uint8 status;
}usart_error_status_t;

typedef struct{
    uint32 buadrate;
    uint8 usart_speed;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;
#if USART_RX_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE       
    void (* USART_RxDefaulteinterruptHandler) (void); 
#endif
#if USART_RX_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE    
    void (* USART_TxDefaulteinterruptHandler) (void); 
#endif
    void (* USART_FramingErrorHandler) (void); 
    void (* USART_OverRunErrorHandler) (void); 
   
}usart_t;

/*........section: function declarations......... */
std_returntype USART_ASYNC_Init(const usart_t * _usart );
std_returntype USART_ASYNC_DiInit(const usart_t * _usart );
std_returntype USART_ReadByteBlocking(uint8 *_data );
std_returntype USART_ReadByteNonBlocking(uint8 *_data );

std_returntype USART_WriteByteNonBlocking(uint8 _data );
std_returntype USART_WriteStringNonBlocking(uint8 *_data,uint16 str_len );
std_returntype USART_WriteByteBlocking(uint8 _data );
std_returntype USART_WriteStringBlocking(uint8 *_data,uint16 str_len );

#endif	/* HAL_USART_H */

