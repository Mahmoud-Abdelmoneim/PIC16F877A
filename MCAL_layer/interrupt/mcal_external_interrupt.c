#include "mcal_external_interrupt.h"

static InterruptHandler INT0_InterruptHandler=NULL;
static InterruptHandler RB4_InterruptHandler_HIGH=NULL;
static InterruptHandler RB4_InterruptHandler_LOW=NULL;
static InterruptHandler RB5_InterruptHandler_HIGH=NULL;
static InterruptHandler RB5_InterruptHandler_LOW=NULL;
static InterruptHandler RB6_InterruptHandler_HIGH=NULL;
static InterruptHandler RB6_InterruptHandler_LOW=NULL;
static InterruptHandler RB7_InterruptHandler_HIGH=NULL;
static InterruptHandler RB7_InterruptHandler_LOW=NULL;



static std_returntype External_INTx_enable(const inteerrupt_INTx_t* int_obj);
static std_returntype External_INTx_disable(const inteerrupt_INTx_t* int_obj);
static std_returntype External_edge_Init(const inteerrupt_INTx_t* int_obj);
static std_returntype External_INTx_Pin_Init(const inteerrupt_INTx_t* int_obj);
static std_returntype External_INTx_Clear_Flag(const inteerrupt_INTx_t* int_obj);

static std_returntype SetInterruptHandler(void (*InterruptHandler)(void));
static std_returntype Interrupt_INTx_SetInterruptHandler(const inteerrupt_INTx_t* int_obj);


static std_returntype External_RBx_enable(const inteerrupt_RBx_t* int_obj);
static std_returntype External_RBx_disable(const inteerrupt_RBx_t* int_obj);
static std_returntype External_RBx_Pin_Init(const inteerrupt_RBx_t* int_obj);
/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_INT0_Init(const inteerrupt_INTx_t* int_obj)
{
    std_returntype ret=E_OK;
    
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        /*disable external interrupt */
        ret |= External_INTx_disable(int_obj);
        /*clear interrupt flag: external interrupt did not occur*/
        ret |= External_INTx_Clear_Flag(int_obj);
        /*configure external interrupt edge*/
        ret |= External_edge_Init(int_obj);
        /*configure external interrupt I/O pin */
        ret |= External_INTx_Pin_Init(int_obj);
        /*configure default interrupt callback*/
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        /*enable external interrupt */
        ret |= External_INTx_enable(int_obj);
        
    }
    return ret;
}


void INT0_ISR(void){
    /*the INT0 external interrupt occur (the interrupt flag must be clear)*/
    EXT_INT0_InterruptFlagClear();
    /*code*/
    
    /*callback function gets called every time ISR executes */
    if(INT0_InterruptHandler) {INT0_InterruptHandler();}
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_INT0_DeInit(const inteerrupt_INTx_t* int_obj)
{
    std_returntype ret=E_OK; 
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        ret = External_INTx_disable(int_obj);
    
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_RBx_Init(const inteerrupt_RBx_t* int_obj)
{
    std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
           /* This routine clears the interrupt disable for the external interrupt, RBx */
        EXT_RORTB_InterruptDisable();
        /*........this routine clear bit for interrupt flag the external RORTB....*/
        EXT_RORTB_InterruptFlagClear();
        /*this macro set global interrupt enable */
        INTERRUPT_Golableinterruptenable();
        /*this macro set peripheral interrupt enable */
        INTERRUPT_peripheralinterruptenable();
        /* Initialize the RBx pin to be input */
        ret = gpio_pin_diriction_initailize(&(int_obj->mcu_pin));
        /* Initialize the call back functions */
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4:
                RB4_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler_HIGH=int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW=int_obj->EXT_InterruptHandler_LOW;
                break;
            default:ret = E_NOT_OK;;     
        
        }    
        EXT_RORTB_InterruptEnable();
        ret = E_OK;
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_returntype External_Interrupt_RBx_DeInit(const inteerrupt_RBx_t* int_obj)
{
    std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        
    
    }
    return ret;
}
/*................................................................*/
/*.....static function for INTx external interrupt...............*/
/*..............................................................*/

/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_INTx_enable(const inteerrupt_INTx_t* int_obj){
     std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
          switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT0:
                INTERRUPT_Golableinterruptenable();
                INTERRUPT_peripheralinterruptenable();
                EXT_INT0_InterrupEnable();
                ret=E_OK;
                break;
            
            default : ret=E_NOT_OK  ;    
        ret=E_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_INTx_disable(const inteerrupt_INTx_t* int_obj){
     std_returntype ret=E_OK;
    
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptDisable();
                ret=E_OK;
                break;
            
            default : ret=E_NOT_OK  ;    
        ret=E_OK;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_edge_Init(const inteerrupt_INTx_t* int_obj){
        std_returntype ret=E_OK; 
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT0:
                if(int_obj->edge == INTERRUPT_RISING_EDGE)      EXT_INT0_RisingEdgeSet();
                else if(int_obj->edge == INTERRUPT_FALLING_EDGE) EXT_INT0_FallingEdgeSet();
                else {/*nothing*/}
                ret=E_OK;
                break;
            
            default : ret=E_NOT_OK  ;    
        ret=E_OK;
        }       
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_INTx_Pin_Init(const inteerrupt_INTx_t* int_obj){
     std_returntype ret=E_OK; 
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        gpio_pin_diriction_initailize(&(int_obj->mcu_pin));
    }
    return ret;
}
  /*---------------------------------------------------------------*/
 /*.....static function for PORTB external interrupt..............*/
/*---------------------------------------------------------------*/

/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_RBx_enable(const inteerrupt_RBx_t* int_obj){
    std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
 
    }

    return ret;
}

void RB4_ISR(uint8 RB4_source){
    /*the INT0 external interrupt occur (the interrupt flag must be clear)*/
    EXT_RORTB_InterruptFlagClear();
    /*code*/
    
    /*callback function gets called every time ISR executes */
    if(RB4_source==1){
        if(RB4_InterruptHandler_HIGH) {RB4_InterruptHandler_HIGH();}
        else {/*nothing*/}
    }
    else if(RB4_source==0){
        if(RB4_InterruptHandler_LOW)  {RB4_InterruptHandler_LOW();}
        else {/*nothing*/}
    }
    else {/*nothing*/}
}

void RB5_ISR(uint8 RB5_source){
    /*the INT0 external interrupt occur (the interrupt flag must be clear)*/
    EXT_RORTB_InterruptFlagClear();
    /*code*/
    
    /*callback function gets called every time ISR executes */
    if(RB5_source==1){
        if(RB5_InterruptHandler_HIGH) {RB5_InterruptHandler_HIGH();}
        else {/*nothing*/}
    }
    else if(RB5_source==0){
        if(RB5_InterruptHandler_LOW)  {RB5_InterruptHandler_LOW();}
        else {/*nothing*/}
    }
}
void RB6_ISR(uint8 RB6_source){
    /*the INT0 external interrupt occur (the interrupt flag must be clear)*/
    EXT_RORTB_InterruptFlagClear();
    /*code*/
    
    /*callback function gets called every time ISR executes */
    if(RB6_source==1){
        if(RB6_InterruptHandler_HIGH) {RB6_InterruptHandler_HIGH();}
        else {/*nothing*/}
    }
    else if(RB6_source==0){
        if(RB6_InterruptHandler_LOW)  {RB6_InterruptHandler_LOW();}
        else {/*nothing*/}
    }
}
void RB7_ISR(uint8 RB7_source){
    /*the INT0 external interrupt occur (the interrupt flag must be clear)*/
    EXT_RORTB_InterruptFlagClear();
    /*code*/
    
    /*callback function gets called every time ISR executes */
   if(RB7_source==1){
        if(RB7_InterruptHandler_HIGH) {RB7_InterruptHandler_HIGH();}
        else {/*nothing*/}
    }
    else if(RB7_source==0){
        if(RB7_InterruptHandler_LOW)  {RB7_InterruptHandler_LOW();}
        else {/*nothing*/}
    } 
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_RBx_disable(const inteerrupt_RBx_t* int_obj){
    std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        
    
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_RBx_Pin_Init(const inteerrupt_RBx_t* int_obj){
    std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
     
        
    
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype External_INTx_Clear_Flag(const inteerrupt_INTx_t* int_obj){
    std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
         switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_InterruptFlagClear();
                ret=E_OK;
                break;
            
            default : ret=E_NOT_OK  ;    
        ret=E_OK;
        }
    }
    return ret;
}

/**
 * 
 * @param InterruptHandler
 * @return 
 */
static std_returntype SetInterruptHandler(void (*InterruptHandler)(void)){
    std_returntype ret=E_OK;
    if(NULL==InterruptHandler)
        ret=E_NOT_OK;
    else{
        INT0_InterruptHandler=InterruptHandler;
        ret = E_OK;
    
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static std_returntype Interrupt_INTx_SetInterruptHandler(const inteerrupt_INTx_t* int_obj){
    std_returntype ret=E_OK;
    if(NULL==int_obj)
        ret=E_NOT_OK;
    else{
        switch(int_obj->source){
            
            case INTERRUPT_EXTERNAL_INT0:
                ret = SetInterruptHandler(int_obj->EXT_InterruptHandler);
                
                break;
            
            default : ret=E_NOT_OK  ;    
        ret=E_OK;
        }
    }
    return ret;
}