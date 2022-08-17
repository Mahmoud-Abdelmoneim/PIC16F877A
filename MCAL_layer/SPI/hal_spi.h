/* 
 * File:   hal_spi.h
 * Author: El-Wattaneya
 *
 * Created on 11 ?????, 2022, 02:11 ?
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/*........section include.........*/
#include "../pic16f877a.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../mcal_std_types.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"

/*........section: macro declarations......... */
#define SPI_CLOCK_POLARITY_SELECT_HIGH                 1      
#define SPI_CLOCK_POLARITY_SELECT_LOW                  0

#define SPI_CLOCK_PHASE_SELECT_HIGH                    1      
#define SPI_CLOCK_PHASE_SELECT_LOW                     0
  
#define SPI_DATA_SAMPLED_AT_END                        1
#define SPI_DATA_SAMPLED_AT_MIDDLE                     0

#define SPI_BUFFER_STATUS_FULL                         1
#define SPI_BUFFER_STATUS_EMPTY                        0

#define SPI_SYNCHRONOUS_SERIAL_PORT_ENABLE             1
#define SPI_SYNCHRONOUS_SERIAL_PORT_DISABLE            0

#define SPI_SLAVE_MODE_SS_PIN_DISABLED                 0x05
#define SPI_SLAVE_MODE_SS_PIN_ENABLED                  0x04
#define SPI_MASTER_MODE_CLK_TMR2                       0x03
#define SPI_MASTER_MODE_CLK_FOSC_DIV_64                0x02
#define SPI_MASTER_MODE_CLK_FOSC_DIV_16                0x01
#define SPI_MASTER_MODE_CLK_FOSC_DIV_4                 0x00

/*........section: macro function declarations......... */
#define SPI_CLOCK_POLARITY_SELECT(_POLARITY)       (SSPCONbits.CKP=_POLARITY)

#define SPI_CLOCK_PHASE_SELECT(_PHASE)             (SSPSTATbits.CKE=_PHASE)

#define SPI_DATA_SAMPLED_SELECT(_SAMPLED)          (SSPSTATbits.SMP=_SAMPLED)

#define SPI_SYNCHRONOUS_SELECT_MODE(_MODE)         (SSPCONbits.SSPM=_MODE)

#define SPI_SYNCHRONOUS_SERIAL_PORT(_ENABLE)       (SSPCONbits.SSPEN=_ENABLE)
/*........section: data type declarations......... */

typedef struct{
    uint8 clk_polarity;
    uint8 clk_phase;
    uint8 data_sampled;
    uint8 spi_mode;
#if SPI_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE  
    void (* SPI_interruptHandler) (void);
#endif    
}spi_t;
/*........section: function declarations......... */
std_returntype SPI_Init(spi_t *_spi_obj);
std_returntype SPI_DeInit(spi_t *_spi_obj);
std_returntype SPI_SendByte(spi_t *_spi_obj,uint8 _data);
std_returntype SPI_ReadByte(spi_t *_spi_obj,uint8 *_data);

#endif	/* HAL_SPI_H */

