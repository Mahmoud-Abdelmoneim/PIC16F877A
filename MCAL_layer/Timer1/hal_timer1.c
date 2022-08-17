#include "hal_timer1.h"
static uint16 timer1_preload=0;
static inline void TMR1_Mode_Select(const timer1_t * _timer1);
static inline void TMR1_Prescaler_Config(const timer1_t * _timer1);

#if TIMER1_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
static void (*Timer1_InterruptHandler)(void)=NULL;
#endif
/**
 * 
 * @param _timer1
 * @return 
 */
std_returntype Timer1_Init(const timer1_t * _timer1){
    std_returntype ret=E_OK;
    if(NULL==_timer1)
        ret=E_NOT_OK;
    else
    {
        TIMER1_MODULE_DISABLE();
        TIMER1_PRESCALER_SELECT(_timer1->perscaler_value);
        TMR1_Mode_Select(_timer1);
        TMR1H=(_timer1->timer1_preload_value)>>8;
        TMR1L=(uint8)(_timer1->timer1_preload_value);
        timer1_preload=_timer1->timer1_preload_value;
        /*interrupt configuration*/
#if TIMER1_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
        TIMER1_InterruptFlagClear();
        TIMER1_InterrupEnable();
        INTERRUPT_Golableinterruptenable();
        INTERRUPT_peripheralinterruptenable();
        
        Timer1_InterruptHandler=_timer1->TIMER1_InterruptHandler;
#endif
        TIMER1_MODULE_ENABLE() ;
        ret=E_OK;
    }
   return ret;
  }
/**
 * 
 * @param _timer1
 * @return 
 */
std_returntype Timer1_DeInit(const timer1_t * _timer1){
    std_returntype ret=E_OK;
    if(NULL==_timer1)
        ret=E_NOT_OK;
    else
    {
        TIMER1_MODULE_DISABLE();
#if TIMER1_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
        TIMER1_InterruptDisable();
#endif        
        ret=E_OK;
    }
   return ret;
  }
/**
 * 
 * @param _timer1
 * @param value
 * @return 
 */
std_returntype Timer1_Write_Value(const timer1_t * _timer1,uint16 value){
    std_returntype ret=E_OK;
    if(NULL==_timer1)
        ret=E_NOT_OK;
    else
    {
        TMR1H=(value)>>8;
        TMR1L=(uint8)(value);
       
        ret=E_OK;
    }
   return ret;
  }
/**
 * 
 * @param _timer1
 * @param value
 * @return 
 */
std_returntype Timer1_Read_Value(const timer1_t * _timer1,uint16* value){
    std_returntype ret=E_OK;
    uint8 l_tmr1h=0,l_tmr1l=0;
    if(NULL==_timer1  || NULL==value)
        ret=E_NOT_OK;
    else
    {
       l_tmr1h=TMR1H;
       l_tmr1l=TMR1L;
       *value=(uint16)((l_tmr1h<<8)+l_tmr1l);
       
        ret=E_OK;
    }
   return ret;
  }
/**
 * 
 */
#if TIMER1_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE

void TIM1_ISR(void){
    TIMER1_InterruptFlagClear();
    TMR1H=(timer1_preload)>>8;
    TMR1L=(uint8)(timer1_preload);
    
    if(Timer1_InterruptHandler)
        Timer1_InterruptHandler();
}
#endif
/**
 * 
 * @param _timer1
 */
static inline void TMR1_Mode_Select(const timer1_t * _timer1){
    if(TIMER1_TIMER_MODE==_timer1->timer1_mode){
       TIMER1_SELECT_TIMER_MODE();
        
    }
    else if(TIMER1_COUNTER_MODE==_timer1->timer1_mode){
        TIMER1_SELECT_COUNTER_MODE();
        if(TIMER1_ASYN_COUNTER_MODE==_timer1->timer1_counter_syn_mode)
            TIMER1_ASYN_COUNTER_MODE_ENABLE();
        else if(TIMER1_SYN_COUNTER_MODE==_timer1->timer1_counter_syn_mode)
            TIMER1_SYN_COUNTER_MODE_ENABLE();
        else{/*nothing*/}
    }  
    else{/*nothing*/}
    
}