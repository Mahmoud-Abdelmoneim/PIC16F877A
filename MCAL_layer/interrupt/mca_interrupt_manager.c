#include "mcal_interrupt_manager.h"
static volatile uint8 RB4_flag=1,RB5_flag=1,RB6_flag=1,RB7_flag=1;
void __interrupt() ISR(void)
{
    
    if(INTCONbits.INTF==INTERRUPT_OCCUR)
    {
        INT0_ISR();
    
    }
    else {}
    if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB4==GPIO_HIGH) &&(RB4_flag==1))
    {
        RB4_flag=0;
        RB4_ISR(0);
    
    }
    else{ }
     if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB4==GPIO_LOW) && (RB4_flag==0))
    {
         RB4_flag=1;
        RB4_ISR(1);
    
    }
    else{ }
    
     if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB5==GPIO_HIGH) && (RB5_flag==1))
    {
        RB5_flag=0;
        RB5_ISR(0);
    
    }
    else{ }
     if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB5==GPIO_LOW) && (RB5_flag==0))
    {
        RB5_flag=1; 
        RB5_ISR(1);
    
    }
    else{ }
    
    
    if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB6==GPIO_HIGH) && (RB6_flag==1))
    {
        RB6_flag=0;
        RB6_ISR(0);
    
    }
    else{ }
     if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB6==GPIO_LOW) && (RB6_flag==0))
    {
        RB6_flag=1;
        RB6_ISR(1);
    
    }
    else{ }
    
    
    if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB7==GPIO_HIGH) && (RB7_flag==1))
    {
        RB7_flag=0;
        RB7_ISR(0);
    
    }
    else{ }
     if(INTCONbits.RBIF==INTERRUPT_OCCUR && (PORTBbits.RB7==GPIO_LOW) && (RB7_flag==0))
    {
        RB7_flag=1;
        RB7_ISR(1);
    
    }
    else{ }
    
     if(PIR1bits.ADIF==INTERRUPT_OCCUR )
    {
         
         ADC_ISR();
         
    
    }
    else{ }
    if(INTCONbits.T0IF==INTERRUPT_OCCUR )
    {         
         TIM0_ISR();          
   }
#if TIMER1_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE    
    if(PIR1bits.TMR1IF==INTERRUPT_OCCUR )
    {  
         TIM1_ISR();
    }
    else{}
#endif    
#if TIMER2_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE    
    if(PIR1bits.TMR2IF==INTERRUPT_OCCUR )
    {  
         TIM2_ISR();
    }
    else{ }
#endif    
#if CCP1_INTERRUPT_FEATIRE_ENABLE  ==   INTERRUPT_FEATIRE_ENABLE
    if(PIR1bits.CCP1IF==INTERRUPT_OCCUR )
    {  
         CCP1_ISR();
    }
    else{ /*nothing*/}
#endif
#if CCP2_INTERRUPT_FEATIRE_ENABLE   ==  INTERRUPT_FEATIRE_ENABLE    

    if(PIR2bits.CCP2IF==INTERRUPT_OCCUR )
    {  
         CCP2_ISR();
    }
    else{ /*nothing*/}
#endif
#if USART_TX_INTERRUPT_FEATIRE_ENABLE  ==  INTERRUPT_FEATIRE_ENABLE
 
    if(PIR1bits.TXIF==INTERRUPT_OCCUR )
    {  
         USART_TX_ISR();
    }
    else{ /*nothing*/}
#endif
    
#if USART_RX_INTERRUPT_FEATIRE_ENABLE  ==  INTERRUPT_FEATIRE_ENABLE       
     if(PIR1bits.RCIF==INTERRUPT_OCCUR )
    {  
         USART_RX_ISR();
    }
    else{ /*nothing*/}
#endif
#if SPI_INTERRUPT_FEATIRE_ENABLE  ==  INTERRUPT_FEATIRE_ENABLE    
    if(PIR1bits.SSPIF==INTERRUPT_OCCUR )
    {  
         SPI_ISR();
    }

    else{ /*nothing*/}
#endif
#if MSSP_I2C_INTERRUPT_FEATIRE_ENABLE  ==  INTERRUPT_FEATIRE_ENABLE    
    if(PIR1bits.SSPIF==INTERRUPT_OCCUR )
    {  
         I2C_ISR();
    }

    else{ /*nothing*/}
    if(PIE2bits.BCLIE == INTERRUPT_OCCUR){
        I2C_BC_ISR();
    }
    
#endif    
}
