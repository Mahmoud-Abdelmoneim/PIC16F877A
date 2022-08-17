#include "hal_ccp.h"
static void CCP_Interrupt_Config(const ccp_t* _ccp_obj);
static void CCP_Pwm_config_mode(const ccp_t* _ccp_obj);
#if CCP1_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
static void (*CCP1_InterruptHandler)(void)=NULL;
#endif
#if CCP2_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
static void (*CCP2_InterruptHandler)(void)=NULL;
#endif
/**
 * 
 * @param _ccp1_obj
 * @return 
 */
std_returntype CCP_Init(const ccp_t* _ccp_obj){
     std_returntype ret=E_OK;
    if(NULL==_ccp_obj)
        ret=E_NOT_OK;
    else
    {
        if(_ccp_obj->ccp_inst == CCP1_INST){
             CCP1_SET_MODE(CCP_MODULE_DESABLE);
        }
        else if(_ccp_obj->ccp_inst == CCP1_INST){
             CCP2_SET_MODE(CCP_MODULE_DESABLE);
        }
       
        
        if(_ccp_obj->ccp_mode==CCP_CAPTURE_MODE_SELECTED){
            switch(_ccp_obj->ccp_mode_variant){
                case CCP_CAPTURE_MODE_FALLING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_FALLING_EDGE);break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_1_RISING_EDGE);break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_4_RISING_EDGE);break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP1_SET_MODE(CCP_CAPTURE_MODE_16_RISING_EDGE);break;
                default:ret=E_NOT_OK ;
            }
        }
        else if(_ccp_obj->ccp_mode==CCP1_COMPARE_MODE_SELECTED){
            switch(_ccp_obj->ccp_mode_variant){
                case CCP_COMPARE_MODE_SET_PIN_LOW:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_LOW);break;
                case CCP_COMPARE_MODE_SET_PIN_HIGH:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_SET_PIN_HIGH);break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);break;
                case CCP_COMPARE_MODE_GEN_EVENT:
                    CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);break;
                default:ret=E_NOT_OK ;
            }
            
        }
#if  (CCP1_CFG_SELECTED_MODE == CCP_CFG_PWN_MODE_SELSECT  ) || (CCP2_CFG_SELECTED_MODE == CCP_CFG_PWN_MODE_SELSECT  )        
        else if(_ccp_obj->ccp_mode==CCP_PWM_MODE_SELECTED){
           CCP_Pwm_config_mode(_ccp_obj);
           
        }
        else{/*nothing*/}
#endif
        ret = gpio_pin_initailize(&(_ccp_obj->ccp_pin));
        CCP_Interrupt_Config(_ccp_obj);
    }       
      return ret;
   }
/**
 * 
 * @param _ccp1_obj
 * @return 
 */
std_returntype CCP1_DeInit(const ccp_t* _ccp_obj){
     std_returntype ret=E_OK;
    if(NULL==_ccp_obj)
        ret=E_NOT_OK;
    else
    {
        if(_ccp_obj->ccp_inst == CCP1_INST){
             CCP1_SET_MODE(CCP_MODULE_DESABLE);
#if CCP1_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE       
        CCP1_InterruptDisable();
#endif             
        }
        else if(_ccp_obj->ccp_inst == CCP1_INST){
             CCP2_SET_MODE(CCP_MODULE_DESABLE);
#if CCP2_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE       
        CCP2_InterruptDisable();
#endif              
        }

       
    } 
     return ret; 
   }
/**
 * 
 * @param _cpp
 * @param _duty
 * @return 
 */
#if CCP1_CFG_SELECTED_MODE == CCP1_CFG_CAPTURE_MODE_SELSECT    
std_returntype CCP_IsCaptureDataReady(uint8 * _capture_status){
    std_returntype ret=E_OK;
    if(NULL==_capture_status)
        ret=E_NOT_OK;
    else
    {
        if(PIR1bits.CCP1IF == CCP_CAPTURE_READY){
            * _capture_status = CCP_CAPTURE_READY;
            CCP1_InterruptFlagClear() ;
        }
        else{
            * _capture_status = CCP_CAPTURE_NOT_READY;
        }


    } 
      return ret;
    }
/**
 * 
 * @param _cpp
 * @param _duty
 * @return 
 */
std_returntype CCP_Capture_Mode_Read_Value(uint16 * _capture_value){
    std_returntype ret=E_OK;
    CCP_GEG_T ccp1_value;
    if(NULL==_capture_value)        
        ret=E_NOT_OK;
    else
    {
        ccp1_value.ccpr_low =  CCPR1L;
        ccp1_value.ccpr_high = CCPR1H;
        *_capture_value = ccp1_value.ccpr_16bit;

    } 
      return ret;
}
#endif 
/**
 * 
 * @param _cpp
 * @param _duty
 * @return 
 */
#if  CCP1_CFG_SELECTED_MODE == CCP1_CFG_COMPARE_MODE_SELSECT    
std_returntype CCP1_IsCompareComplete(uint8 * _ccompare_status){
     std_returntype ret=E_OK;
    if(NULL==_ccompare_status)
        ret=E_NOT_OK;
    else
    {
          if(PIR1bits.CCP1IF == CCP1_COMPARE_READY){
            * _ccompare_status = CCP1_COMPARE_READY;
            CCP1_InterruptFlagClear() ;
        }
        else{
            * _ccompare_status = CCP1_COMPARE_NOT_READY;
        }

    
    } 
     return ret; 
   }
/**
 * 
 * @param _cpp
 * @param _duty
 * @return 
 */
std_returntype CCP1_Capture_Mode_Set_Value(uint16  _compare_value){
    std_returntype ret=E_OK;
    CCP1_GEG_T ccp1_value;
    ccp1_value.ccpr1_16bit=_compare_value;
    CCPR1L = ccp1_value.ccpr1_low;
    CCPR1H = ccp1_value.ccpr1_high;
    
    return ret; 
   }
#endif 
/**
 * 
 * @param _cpp
 * @param _duty
 * @return 
 */
#if  CCP1_CFG_SELECTED_MODE == CCP_CFG_PWN_MODE_SELSECT    
std_returntype CCP_PWM_Set_duty(const ccp_t* _cpp ,const uint16 _duty){
    uint16 l_duty=0;
    std_returntype ret=E_OK;
    if(NULL==_cpp)
        ret=E_NOT_OK;
    else
    {
        l_duty=(uint16)((PR2+1) * (_duty/100.0) * 4.0);
        if(_cpp->ccp_inst == CCP1_INST){
             CCP1CONbits.CCP1Y =(uint8) (l_duty & 1);
             CCP1CONbits.CCP1X =(uint8) (l_duty & 2);
             CCPR1L=(uint8)(l_duty >> 2);
        }
        else if(_cpp->ccp_inst == CCP2_INST){
             CCP2CONbits.CCP2Y =(uint8) (l_duty & 1);
             CCP2CONbits.CCP2X =(uint8) (l_duty & 2);
             CCPR2L=(uint8)(l_duty >> 2);
        }
    
    }
       ret=E_OK;
       return ret;
   }
/**
 * 
 * @param _cpp
 * @return 
 */
std_returntype CCP_PWM_Sart(const ccp_t* _cpp){
    std_returntype ret=E_OK; 
    if(NULL==_cpp)
        ret=E_NOT_OK;
    else
    {
        if(_cpp->ccp_inst == CCP1_INST){
            CCP1CONbits.CCP1M=CCP_PWM_MODE;
        }
        else if(_cpp->ccp_inst == CCP2_INST){
            CCP2CONbits.CCP2M=CCP_PWM_MODE;
        }       
    }  
    
    ret=E_OK; 
    return ret;
   }

/**
 * 
 * @param _cpp
 * @return 
 */
std_returntype CCP_PWN_Stop(const ccp_t* _cpp){
       std_returntype ret=E_OK;
        if(NULL==_cpp)
        ret=E_NOT_OK;
    else
    {
        if(_cpp->ccp_inst == CCP1_INST){
            CCP1CONbits.CCP1M=CCP_MODULE_DESABLE;
        }
        else if(_cpp->ccp_inst == CCP2_INST){
            CCP2CONbits.CCP2M=CCP_MODULE_DESABLE;
        }       
    } 
       
       ret=E_OK;
       return ret;
   }
#endif 
#if CCP1_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
void CCP1_ISR(void){
    CCP1_InterruptFlagClear();
    if(CCP1_InterruptHandler)
        CCP1_InterruptHandler();
       
}
 #endif
#if CCP2_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
void CCP2_ISR(void){
    CCP2_InterruptFlagClear();
    if(CCP2_InterruptHandler)
        CCP2_InterruptHandler();  
}
 #endif  
//#endif	
#if  CCP1_CFG_SELECTED_MODE == CCP_CFG_PWN_MODE_SELSECT 
static void CCP_Pwm_config_mode(const ccp_t* _ccp_obj){
     if(_ccp_obj->ccp_inst == CCP1_INST){
            if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
                CCP1_SET_MODE(CCP_PWM_MODE);
            }
            }
            else if(_ccp_obj->ccp_inst == CCP2_INST){
                if(CCP_PWM_MODE == _ccp_obj->ccp_mode_variant){
                CCP2_SET_MODE(CCP_PWM_MODE);
            }
            } 
             
            PR2=(uint8)((_XTAL_FREQ / (_ccp_obj->freq_pmw *4.0* _ccp_obj->perscaler_value * 
                    _ccp_obj->postscaler_value)) - 1);
}
#endif
static void CCP_Interrupt_Config(const ccp_t* _ccp_obj){
    #if CCP1_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
       CCP1_InterrupEnable();
       CCP1_InterruptFlagClear();
       INTERRUPT_Golableinterruptenable();
       INTERRUPT_peripheralinterruptenable(); 
       CCP1_InterruptHandler=_ccp_obj->CCP1_InterruptHandler;
#endif  
#if CCP2_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
       CCP2_InterrupEnable();
       CCP2_InterruptFlagClear();
       INTERRUPT_Golableinterruptenable();
       INTERRUPT_peripheralinterruptenable(); 
       CCP2_InterruptHandler=_ccp_obj->CCP1_InterruptHandler;
#endif   
    
}