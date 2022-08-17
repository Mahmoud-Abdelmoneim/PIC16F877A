#include "hal_timer2.h"
static uint8 timer2_preload=0;
#if TIMER2_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
static void (*Timer2_InterruptHandler)(void)=NULL;
#endif
std_returntype Timer2_Init(const timer2_t * _timer2){
    std_returntype ret=E_OK;
    if(NULL==_timer2)
        ret=E_NOT_OK;
    else
    {
        TIMER2_MODULE_DISABLE();
        TIMER2_PRESCALER_SELECT(_timer2->perscaler_value);
        TIMER2_POSTCALER_SELECT(_timer2->postscaler_value);
        TMR2 = _timer2->timer2_preload_value;
        timer2_preload = _timer2->timer2_preload_value;
#if TIMER2_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
        TIMER2_InterruptFlagClear();
        TIMER2_InterrupEnable();
        INTERRUPT_Golableinterruptenable();
        INTERRUPT_peripheralinterruptenable();
        Timer2_InterruptHandler=_timer2->TIMER2_InterruptHandler;
#endif
        TIMER2_MODULE_ENABLE(); 
    }
     return ret;
}
std_returntype Timer2_DeInit(const timer2_t * _timer2){
    std_returntype ret=E_OK;
    if(NULL==_timer2)
        ret=E_NOT_OK;
    else
    {
        TIMER2_MODULE_DISABLE();
#if TIMER2_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
        TIMER2_InterruptDisable();
#endif
    
    }
     return ret;
}

std_returntype Timer2_Write_Value(const timer2_t * _timer2,uint8 value){
    std_returntype ret=E_OK;
    if(NULL==_timer2)
        ret=E_NOT_OK;
    else
    {
        TMR2=value;
    }
     return ret;
}


std_returntype Timer2_Read_Value(const timer2_t * _timer2,uint8* value){
    std_returntype ret=E_OK;
    if(NULL==_timer2 || value == NULL)
        ret=E_NOT_OK;
    else
    {
        *value =(uint8) TMR2;
    }
     return ret;
}
#if TIMER2_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
void TIM2_ISR(void){
    TIMER2_InterruptFlagClear();
    //TMR2=timer2_preload;
    
    if(Timer2_InterruptHandler)
        Timer2_InterruptHandler();
    
}
#endif