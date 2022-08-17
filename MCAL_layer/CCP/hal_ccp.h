/* 
 * File:   hal_ccp1.h
 * Author: El-Wattaneya
 *
 * Created on 01 ?????, 2022, 07:19 ?
 */

#ifndef HAL_CCP1_H
#define	HAL_CCP1_H

/*........section include.........*/
#include "hal_ccp_cfg.h"
#include "../pic16f877a.h"
#include  "../mcal_std_types.h"
#include "../../MCAL_layer/GPIO/hal_gpio.h"
#include "../../MCAL_layer/interrupt/mcal_internal_interrupt.h"
/*........section: macro declarations......... */
#define CCP_MODULE_DESABLE                      ((uint8)0x00)
#define CCP_CAPTURE_MODE_FALLING_EDGE           ((uint8)0x04)
#define CCP_CAPTURE_MODE_1_RISING_EDGE          ((uint8)0x05)
#define CCP_CAPTURE_MODE_4_RISING_EDGE          ((uint8)0x06)
#define CCP_CAPTURE_MODE_16_RISING_EDGE         ((uint8)0x07)
#define CCP_COMPARE_MODE_SET_PIN_LOW            ((uint8)0x08)
#define CCP_COMPARE_MODE_SET_PIN_HIGH           ((uint8)0x09)
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT       ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT              ((uint8)0x0B)
#define CCP_PWM_MODE                            ((uint8)0x0C)

#define CCP_CAPTURE_NOT_READY                    0
#define CCP_CAPTURE_READY                        1

#define CCP_COMPARE_NOT_READY                    0
#define CCP_COMPARE_READY                        1

#define CCP_POSTCALER_DIV_BY_1    1
#define CCP_POSTCALER_DIV_BY_2    2
#define CCP_POSTCALER_DIV_BY_3    3
#define CCP_POSTCALER_DIV_BY_4    4
#define CCP_POSTCALER_DIV_BY_5    5
#define CCP_POSTCALER_DIV_BY_6    6
#define CCP_POSTCALER_DIV_BY_7    7
#define CCP_POSTCALER_DIV_BY_8    8
#define CCP_POSTCALER_DIV_BY_9    9
#define CCP_POSTCALER_DIV_BY_10   10 
#define CCP_POSTCALER_DIV_BY_11   11
#define CCP_POSTCALER_DIV_BY_12   12
#define CCP_POSTCALER_DIV_BY_13   13
#define CCP_POSTCALER_DIV_BY_14   14
#define CCP_POSTCALER_DIV_BY_15   15
#define CCP_POSTCALER_DIV_BY_16   16

#define CCP_PRESCALER_DIV_BY_1    1
#define CCP_PRESCALER_DIV_BY_4    4
#define CCP_PRESCALER_DIV_BY_16   16


/*........section: macro function declarations......... */

#define CCP1_SET_MODE(_CONFIG)                   (CCP1CONbits.CCP1M=_CONFIG)
#define CCP2_SET_MODE(_CONFIG)                   (CCP2CONbits.CCP2M=_CONFIG)
/*........section: data type declarations......... */
typedef union{
    struct {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct{
        uint16 ccpr_16bit;
    };
    
}CCP_GEG_T;
typedef enum{
    CCP_CAPTURE_MODE_SELECTED=0,
    CCP1_COMPARE_MODE_SELECTED,
    CCP_PWM_MODE_SELECTED
        
}ccp_mode_t;

typedef enum{
    CCP1_INST,
    CCP2_INST        
}ccp_inst_t;

typedef struct {
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_variant;
    pin_config_t ccp_pin;
//#if CCP1_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    void (*CCP1_InterruptHandler)(void);
//#endif 
#if CCP2_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    void (*CCP2_InterruptHandler)(void);
#endif 
#if  CCP1_CFG_SELECTED_MODE == CCP_CFG_PWN_MODE_SELSECT    
    uint32 freq_pmw;
    uint16 postscaler_value;
    uint16 perscaler_value;
#endif 
    
}ccp_t;

/*........section: function declarations......... */
std_returntype CCP_Init(const ccp_t* _ccp_obj);
std_returntype CCP1_DeInit(const ccp_t* _ccp_obj);

#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELSECT    
    std_returntype CCP_IsCaptureDataReady(uint8 * _capture_status);
    std_returntype CCP_Capture_Mode_Read_Value(uint16 * _capture_value);
#endif 
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELSECT    
    std_returntype CCP1_IsCompareComplete(uint8 * _ccompare_status);
    std_returntype CCP1_Capture_Mode_Set_Value(uint16  _compare_value);
#endif 
#if CCP1_CFG_SELECTED_MODE == CCP_CFG_PWN_MODE_SELSECT    
   std_returntype CCP_PWM_Set_duty(const ccp_t* _cpp ,const uint16 _duty);
   std_returntype CCP_PWM_Sart(const ccp_t *_cpp);
   std_returntype CCP_PWN_Stop(const ccp_t *_cpp);
#endif     
#endif	/* HAL_CCP1_H */

