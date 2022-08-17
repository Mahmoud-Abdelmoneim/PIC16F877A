/* 
 * File:   hal_adc.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 28 , 2022, 12:16 
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/*........section include.........*/
#include "../pic16f877a.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../mcal_std_types.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
#include "hal_adc_cfg.h"

/*........section: macro declarations......... */

/*All Pins Are Analog And Voltage Rev Are Vss And Vdd*/
#define ADC_AN7_ANALOG_FUNCTIONALITY                0x00
/*All Pins Are Analog And Voltage Rev Are AN3 And Vss*/
#define ADC_AN7_3R_ANALOG_FUNCTIONALITY             0x01
/*All Pins From AN0 To AN4 Are Analog And Voltage Rev Are Vss And Vdd*/
#define ADC_AN4_ANALOG_FUNCTIONALITY                0x02
/*All Pins From AN0 To AN4 Are Analog And Voltage Rev Are AN3 And Vss*/
#define ADC_AN4_3R_ANALOG_FUNCTIONALITY             0x03
/*All Pins From AN0 To AN3 Except AN2 Are Analog And Voltage Rev Are Vss And Vdd*/
#define ADC_AN3_ANALOG_FUNCTIONALITY                0x04
/*All Pins From AN0 To AN3 Except AN2 Are Analog And Voltage Rev Are AN3 And VSS*/
#define ADC_AN3_3R_ANALOG_FUNCTIONALITY             0x05
/*All Pins Are Digital */
#define ADC_ALL_DIGITAL_FUNCTIONALITY               0x06
/*All Pins Are Analog And Voltage Rev Are AN3 And AN2 */
#define ADC_ALL_3R_2R_ANALOG_FUNCTIONALITY          0x07
/*All Pins From AN0 To AN5 Are Analog And Voltage Rev Are Vss And Vdd*/
#define ADC_AN5_ANALOG_FUNCTIONALITY                0x08
/*All Pins From AN0 To AN5 Are Analog And Voltage Rev Are AN3 And Vss*/
#define ADC_AN5_3R_ANALOG_FUNCTIONALITY             0x09
/*All Pins From AN0 To AN5 Are Analog And Voltage Rev Are AN3 And AN2 */
#define ADC_AN5_3R_2R_ANALOG_FUNCTIONALITY          0x0A
/*All Pins From AN0 To AN4 Are Analog And Voltage Rev Are AN3 And AN2*/
#define ADC_AN4_3R_AN2_ANALOG_FUNCTIONALITY         0x0B
/*All Pins From AN0 To AN2 Are Analog And Voltage Rev Are AN3 And AN2*/
#define ADC_AN2_3R_AN2_ANALOG_FUNCTIONALITY         0x0C
/*AN0 Is Analog And Voltage Rev Are Vss And Vdd*/
#define ADC_AN0_ANALOG_FUNCTIONALITY                0x0D
/*AN0 Is Analog  And Voltage Rev Are AN3 And AN2*/
#define ADC_AN0_3R_AN2_ANALOG_FUNCTIONALITY         0x0E
/*--------------------------------------------------------------------------*/
#define ADC_RESULT_RIGHT    0x01U
#define ADC_RESULT_LEFT     0x00U

#define ADC_CONVERSION_COMPLETED  1
#define ADC_CONVERSION_INPROGRESS  0

/*........section: macro function declarations......... */
/*A/D Conversion Status: 1 = A/D conversion in progress / 0 = A/D conversion not in progress*/
#define ADC_CONVERSION_STATUS()             (ADCON0bits.GO_DONE)

/*Start Analog To Digital Conversion*/
#define ADC_START_CONVERSION()              (ADCON0bits.GO_DONE=1)
/*
 * @berf: Analog to Digital Control
 * @Note: ADC_CONVERTER_ENABLE() :  Enable Analog to Digital Control
 *        ADC_CONVERTER_DISABLE() : Disable Analog to Digital Control 
 */
#define ADC_CONVERTER_ENABLE()              (ADCON0bits.ADON=1)
#define ADC_CONVERTER_DISABLE()             (ADCON0bits.ADON=0)

/**
 * @brief Analog To Digital Port Control 
 * @note  
 */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)    (ADCON1bits.PCFG=_CONFIG)

#define ADC_RESULT_RIGHT_FORMAT()                  (ADCON1bits.ADFM=1)
#define ADC_RESULT_LEFT_FORMAT()                   (ADCON1bits.ADFM=0)
/*--------------------------------------------------------------------*/
#define ADC_CONVERSION_CLOCK_FOCS_DIV_2()           (ADCON0bits.ADCS=0x00,ADCON1bits.ADCS2=0) 
#define ADC_CONVERSION_CLOCK_FOCS_DIV_8()           (ADCON0bits.ADCS=0x01,ADCON1bits.ADCS2=0)
#define ADC_CONVERSION_CLOCK_FOCS_DIV_32()          (ADCON0bits.ADCS=0x02,ADCON1bits.ADCS2=0)
#define ADC_CONVERSION_CLOCK_FOCS_DIV_FCR()         (ADCON0bits.ADCS=0x03,ADCON1bits.ADCS2=0)
#define ADC_CONVERSION_CLOCK_FOCS_DIV_4()           (ADCON0bits.ADCS=0x00,ADCON1bits.ADCS2=1) 
#define ADC_CONVERSION_CLOCK_FOCS_DIV_16()          (ADCON0bits.ADCS=0x01,ADCON1bits.ADCS2=1)
#define ADC_CONVERSION_CLOCK_FOCS_DIV_64()          (ADCON0bits.ADCS=0x02,ADCON1bits.ADCS2=1)

/*........section: data type declarations......... */


/**
 *
 *
 */
typedef enum {

    ADC_CHANNEL_AN0=0,
    ADC_CHANNEL_AN1,        
    ADC_CHANNEL_AN2,            
    ADC_CHANNEL_AN3,        
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7       
}adc_channel_select_t;

typedef enum {
    ADC_CONVERSION_CLOCK_FOCS_DIV_2=0,
    ADC_CONVERSION_CLOCK_FOCS_DIV_8,
    ADC_CONVERSION_CLOCK_FOCS_DIV_32,
    ADC_CONVERSION_CLOCK_FOCS_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOCS_DIV_4,
    ADC_CONVERSION_CLOCK_FOCS_DIV_16,
    ADC_CONVERSION_CLOCK_FOCS_DIV_64
           
}adc_conversion_clock_t;


typedef struct{
#if ADC_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE    
    void (* interruptHandler) (void);
#endif    
    adc_channel_select_t adc_channel;
    adc_conversion_clock_t conversion_clock;
    uint8 result_format:1;

}adc_confg_t;

typedef uint16 adc_result_t;
/*........section: function declarations......... */

std_returntype ADC_Init(const adc_confg_t * _adc);
std_returntype ADC_DeInit(const adc_confg_t * _adc);
std_returntype ADC_SelectChannel(const adc_confg_t *_adc, adc_channel_select_t channel);
std_returntype ADC_StartConversion(const adc_confg_t *_adc);
std_returntype ADC_IsConversionDone(const adc_confg_t *_adc, uint8 *conversion_status);
std_returntype ADC_GetConversionResult(const adc_confg_t *_adc, adc_result_t *conversion_result);
std_returntype ADC_GetConversion_Blocking(const adc_confg_t *_adc, adc_channel_select_t channel, 
                                 adc_result_t *conversion_result);
std_returntype ADC_StartConversion_Interrupt(const adc_confg_t *_adc, adc_channel_select_t channel);

#endif	/* HAL_ADC_H */

