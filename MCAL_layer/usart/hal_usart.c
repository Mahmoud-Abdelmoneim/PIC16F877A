#include "hal_usart.h"
//#define _XTAL_FREQ 4000000UL
#if USART_TX_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    static void (*USART_TxDefaulteinterruptHandler)(void)=NULL;
#endif
#if USART_RX_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    static void (*USART_RxDefaulteinterruptHandler)(void)=NULL;
    static void (*USART_FramingErrorHandler)(void)=NULL;
    static void (*USART_OverRunErrorHandler)(void)=NULL;
#endif
static void USART_Buadrate_Calculation(const usart_t * _usart);
static void USART_ASYN_TX_Init(const usart_t * _usart);
static void USART_ASYN_RX_Init(const usart_t * _usart);
std_returntype USART_ASYNC_Init(const usart_t * _usart ){
    std_returntype ret=E_OK;
    if(NULL==_usart)
        ret=E_NOT_OK;
    else
    {
        RCSTAbits.SPEN=USART_MODULE_DISABLE;
        TRISCbits.TRISC6 = 1;
        TRISCbits.TRISC7 = 1;
        USART_Buadrate_Calculation(_usart); 
        USART_ASYN_TX_Init(_usart);
        USART_ASYN_RX_Init(_usart);
        RCSTAbits.SPEN=USART_MODULE_ENABLE;
        
    }
    return ret;
}
std_returntype USART_ASYNC_DiInit(const usart_t * _usart ){
    std_returntype ret=E_OK;
    if(NULL==_usart)
        ret=E_NOT_OK;
    else
    {
        RCSTAbits.SPEN=USART_MODULE_DISABLE;
        
    }
    return ret;
}
std_returntype USART_ReadByteBlocking(uint8 *_data ){
    std_returntype ret=E_OK;
     while(!PIR1bits.RCIF)
         ;
        *_data = RCREG;
        
        /*
    if(NULL==_usart ||_data== NULL)
        ret=E_NOT_OK;
    else
    {
       
    }*/
    return ret;
}
std_returntype USART_ReadByteNonBlocking(uint8 *_data ){
   std_returntype ret=E_OK;
   if(1 == PIR1bits.RCIF){
       *_data = RCREG;
       
   }
   else{
       ret=E_NOT_OK;
   } 
   return ret; 
}
std_returntype USART_WriteByteNonBlocking(uint8 _data ){
    std_returntype ret=E_OK;
    if(1 == TXSTAbits.TRMT){
#if USART_TX_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    USART_TX_InterrupEnable();
#endif
    PIR1bits.TXIF=0;
    __delay_ms(100);
    TXREG = _data;
    }
    else{
       ret=E_NOT_OK;
   } 
   return ret; 
}
std_returntype USART_WriteStringNonBlocking(uint8 *_data,uint16 str_len ){
    std_returntype ret=E_OK;
    
    while(*_data){
        ret = USART_WriteByteNonBlocking(*_data++);
    }
    return ret;
}
std_returntype USART_WriteByteBlocking(uint8 _data ){
    std_returntype ret=E_OK;
    while(!TXSTAbits.TRMT) ;
#if USART_TX_INTERRUPT_FEATIRE_ENABLE==INTERRUPT_FEATIRE_ENABLE
    USART_TX_InterrupEnable();
#endif
    TXREG = _data;
   
    return ret;
}
std_returntype USART_WriteStringBlocking(uint8 *_data,uint16 str_len ){
    std_returntype ret=E_OK;
    
    while(*_data)
        ret = USART_WriteByteBlocking(*_data++);
    
    return ret;
}

static void USART_Buadrate_Calculation(const usart_t * _usart){
    float buadrate;
    switch(_usart->usart_speed){
        case USART_ASYNCHRONOUS_HIGH_SPEED:
            TXSTAbits.SYNC=USART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH=USART_ASYNCHRONOUS_HIGH_SPEED;
            buadrate= (( _XTAL_FREQ )/16 / _usart->buadrate) - 1;
            break;
        case USART_ASYNCHRONOUS_LOW_SPEED:
            TXSTAbits.SYNC=USART_ASYNCHRONOUS_MODE;
            TXSTAbits.BRGH=USART_ASYNCHRONOUS_LOW_SPEED;
            buadrate= ((_XTAL_FREQ )/ 64 / _usart->buadrate) - 1;
            break;
        default: ;     
    }
    SPBRG = (uint8)(uint32)(buadrate);
    
}
static void USART_ASYN_TX_Init(const usart_t * _usart){
    if(_usart->usart_tx_cfg.usart_tx_enable == USART_ASYNCHRONOUS_TX_ENABLE){
        TXSTAbits.TXEN = USART_ASYNCHRONOUS_TX_ENABLE;
#if USART_TX_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
        USART_TxDefaulteinterruptHandler = _usart->USART_TxDefaulteinterruptHandler;
        if(_usart->usart_tx_cfg.usart_tx_interrupt_enable == USART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE){
            PIE1bits.TXIE = USART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE;

           USART_TX_InterrupEnable(); 
           INTERRUPT_Golableinterruptenable();
           INTERRUPT_peripheralinterruptenable();
#endif 
        }
        else if(_usart->usart_tx_cfg.usart_tx_interrupt_enable == USART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE){
            PIE1bits.TXIE = USART_ASYNCHRONOUS_TX_INTERRUPT_DISABLE;

        }
        else {/*nothing*/}


        if(_usart->usart_tx_cfg.usart_tx_9bit_enable == USART_ASYNCHRONOUS_TX_9Bit_ENABLE){
          TXSTAbits.TX9=USART_ASYNCHRONOUS_TX_9Bit_ENABLE;
        }
        else if(_usart->usart_tx_cfg.usart_tx_9bit_enable == USART_ASYNCHRONOUS_TX_9Bit_DISABLE){
            TXSTAbits.TX9=USART_ASYNCHRONOUS_TX_9Bit_DISABLE;
        }
        else {/*nothing*/}
    }
    else {/*nothing*/}
    
}

static void USART_ASYN_RX_Init(const usart_t * _usart){
    if(_usart->usart_rx_cfg.usart_rx_enable == USART_ASYNCHRONOUS_RX_ENABLE){
        RCSTAbits.CREN = USART_ASYNCHRONOUS_RX_ENABLE;
#if USART_RX_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
        USART_RxDefaulteinterruptHandler = _usart->USART_RxDefaulteinterruptHandler;
        USART_FramingErrorHandler = _usart->USART_FramingErrorHandler;
        USART_OverRunErrorHandler = _usart->USART_OverRunErrorHandler;
        if(_usart->usart_rx_cfg.usart_rx_interrupt_enable == USART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE){
            PIE1bits.TXIE = USART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE;

           USART_RX_InterrupEnable(); 
           INTERRUPT_Golableinterruptenable();
           INTERRUPT_peripheralinterruptenable();
#endif 
        }
        else if(_usart->usart_rx_cfg.usart_rx_interrupt_enable == USART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE){
            PIE1bits.RCIE = USART_ASYNCHRONOUS_RX_INTERRUPT_DISABLE;

        }
        else {/*nothing*/}


        if(_usart->usart_rx_cfg.usart_rx_9bit_enable == USART_ASYNCHRONOUS_RX_9Bit_ENABLE){
            RCSTAbits.RX9=USART_ASYNCHRONOUS_TX_9Bit_ENABLE;
        }
        else if(_usart->usart_rx_cfg.usart_rx_9bit_enable == USART_ASYNCHRONOUS_RX_9Bit_DISABLE){
            RCSTAbits.RX9=USART_ASYNCHRONOUS_RX_9Bit_DISABLE;
        }
        else {/*nothing*/}
    }
    else {/*nothing*/} 
}
void USART_TX_ISR(void){
    USART_TX_InterruptDisable();
    if(USART_TxDefaulteinterruptHandler)
        USART_TxDefaulteinterruptHandler();
}
void USART_RX_ISR(void){
    if(USART_RxDefaulteinterruptHandler)
        USART_RxDefaulteinterruptHandler();
    
    if(USART_FramingErrorHandler)
        USART_FramingErrorHandler();
    
    if(USART_OverRunErrorHandler)
        USART_OverRunErrorHandler();
    
}
