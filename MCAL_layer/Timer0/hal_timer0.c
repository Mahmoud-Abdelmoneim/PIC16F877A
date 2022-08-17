#include "hal_timer0.h"
static uint8 timer0_preload=0;
static inline void TMR0_Prescaler_Config(const timer0_t * _timer0);
static inline void TMR0_Mode_Select(const timer0_t * _timer0);
static void (*Timer0_InterruptHandler)(void)=NULL;


std_returntype Timer0_Init(const timer0_t * _timer0){
    std_returntype ret=E_OK;
    
    if(NULL==_timer0)
        ret=E_NOT_OK;
    else
    {
        TMR0_Prescaler_Config(_timer0);
        TMR0_Mode_Select(_timer0);
        TMR0=_timer0->timer0_preload_value;
        timer0_preload=_timer0->timer0_preload_value;
        INTERRUPT_Golableinterruptenable();
        INTERRUPT_peripheralinterruptenable();
        TIMER0_InterrupEnable();
        TIMER0_InterruptFlagClear() ;   
        Timer0_InterruptHandler=_timer0->Timer0_InterruptHandler;
    }
   return ret;
}
std_returntype Timer0_DeInit(const timer0_t * _timer0){
    std_returntype ret=E_OK;
    
    if(NULL==_timer0)
        ret=E_NOT_OK;
    else
    {
        TIMER0_InterruptDisable();
    }
   return ret;
}
std_returntype Timer0_Write_Value(const timer0_t * _timer0,uint8 value){
    std_returntype ret=E_OK;
    
    if(NULL==_timer0)
        ret=E_NOT_OK;
    else
    {
        TMR0=value;

    }
   return ret;
}
std_returntype Timer0_Read_Value(const timer0_t * _timer0,uint8* value){
    std_returntype ret=E_OK;
    
    if(NULL==_timer0 || value==NULL)
        ret=E_NOT_OK;
    else
    {
        * value=TMR0;
    }
   return ret;
}

void TIM0_ISR(void){
    TMR0=timer0_preload;
    TIMER0_InterruptFlagClear();
    if(Timer0_InterruptHandler)
        Timer0_InterruptHandler();

}

static inline void TMR0_Prescaler_Config(const timer0_t * _timer0){
    if(TIMER0_PERSCALER_ENABLE_CFG==_timer0->perscaler_enable){
        TIMER0_PERSCALER_ENABLE();
        OPTION_REGbits.PSA=_timer0->timer0_preload_value;
    }
    else if(TIMER0_PERSCALER_DISABLE_CFG==_timer0->perscaler_enable){
        TIMER0_PERSCALER_DISABLE() ;
        
    }  
    else{/*nothing*/}
    
}
static inline void TMR0_Mode_Select(const timer0_t * _timer0){
    if(TIMER0_TIMER_MODE==_timer0->timer0_mode){
       TIMER0_SELECT_TIMER_MODE();
        
    }
    else if(TIMER0_COUNTER_MODE==_timer0->timer0_mode){
        TIMER0_SELECT_COUNTER_MODE();
        if(TIMER0_RISING_EDGE==_timer0->timer0_counter_edge)
            TIMER0_RISING_EDGE_ENABLE();
        else if(TIMER0_FALLING_EDGE==_timer0->timer0_counter_edge)
            TIMER0_FALLING_EDGE_ENABLE(); 
        else {/*nothing*/}
        
    }  
    else{/*nothing*/}
    
}