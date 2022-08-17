/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
#include "MCAL_layer/usart/hal_usart.h"
#include "ECU_layer/button/euc_button.h"
//led_t led={.port_name=PORTB_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
//led_t led1={.port_name=PORTB_INDEX,.pin=GPIO_PIN1,.led_status=LED_OFF};
//volatile uint8 flag=0;
//uint8 value;
//void TX_interr(){
//     std_returntype ret=E_NOT_OK;
//     
//   
//}
//uint8 data=0;
//void RX_interr(){
//    std_returntype ret =E_NOT_OK;
//    
//    ret = USART_ReadByteNonBlocking(&data);
//    if('a'==data){
//        led_turn_on(&led);
//    }
//    else  if('b'==data){
//        led_turn_off(&led);
//    }
//    else  if('c'==data){
//        led_turn_on(&led1);
//    }
//    else  if('d'==data){
//        led_turn_off(&led1);
//    }
//
//}
botton_state_t status_btn1=BUTTON_RELEASED;
button_t btn1={
  .button_connection= BUTTON_ACTIVE_HIGH,
  .button_pin.port=PORTB_INDEX,
  .button_pin.pin=GPIO_PIN0,
  .button_pin.direction=GPIO_DIRICTION_INPUT,
  .button_state=BUTTON_RELEASED
};
botton_state_t status_btn2=BUTTON_RELEASED;
button_t btn2={
  .button_connection= BUTTON_ACTIVE_HIGH,
  .button_pin.port=PORTB_INDEX,
  .button_pin.pin=GPIO_PIN1,
  .button_pin.direction=GPIO_DIRICTION_INPUT,
  .button_state=BUTTON_RELEASED
};
botton_state_t status_btn3=BUTTON_RELEASED;
button_t btn3={
  .button_connection= BUTTON_ACTIVE_HIGH,
  .button_pin.port=PORTB_INDEX,
  .button_pin.pin=GPIO_PIN2,
  .button_pin.direction=GPIO_DIRICTION_INPUT,
  .button_state=BUTTON_RELEASED
};
botton_state_t status_btn4=BUTTON_RELEASED;
button_t btn4={
  .button_connection= BUTTON_ACTIVE_HIGH,
  .button_pin.port=PORTB_INDEX,
  .button_pin.pin=GPIO_PIN3,
  .button_pin.direction=GPIO_DIRICTION_INPUT,
  .button_state=BUTTON_RELEASED
};

void usart_init(void){
    usart_t usart_obj;
    std_returntype ret=E_NOT_OK; 
    usart_obj.buadrate=9600;
    usart_obj.usart_tx_cfg.usart_tx_enable=USART_ASYNCHRONOUS_TX_ENABLE;
    usart_obj.usart_tx_cfg.usart_tx_9bit_enable=USART_ASYNCHRONOUS_TX_9Bit_DISABLE;
    usart_obj.usart_tx_cfg.usart_tx_interrupt_enable=USART_ASYNCHRONOUS_TX_INTERRUPT_ENABLE;
    usart_obj.usart_speed=USART_ASYNCHRONOUS_HIGH_SPEED;
    
    usart_obj.usart_rx_cfg.usart_rx_enable=USART_ASYNCHRONOUS_RX_ENABLE;
    usart_obj.usart_rx_cfg.usart_rx_9bit_enable=USART_ASYNCHRONOUS_RX_9Bit_DISABLE;
    usart_obj.usart_rx_cfg.usart_rx_interrupt_enable=USART_ASYNCHRONOUS_RX_INTERRUPT_ENABLE;
    
    usart_obj.USART_FramingErrorHandler=NULL;
    usart_obj.USART_OverRunErrorHandler=NULL;
    usart_obj.USART_RxDefaulteinterruptHandler=NULL;
    usart_obj.USART_TxDefaulteinterruptHandler=NULL;
    ret = USART_ASYNC_Init(&usart_obj);
}
uint8 data_resived=0;
std_returntype ret=E_NOT_OK; 
int main() {
//    ret = led_intialize(&led);
//    ret = led_intialize(&led1);
    ret = button_intialize(&btn1);
    ret = button_intialize(&btn2);
    ret = button_intialize(&btn3);
    ret = button_intialize(&btn4);
    usart_init();
    TRISD=0;
    PORTDbits.RD0=0;
    while(1)
    {
        ret = USART_WriteByteBlocking('a');
          PORTDbits.RD0=0;
          __delay_ms(1000);
          ret = USART_WriteByteBlocking('b');
         PORTDbits.RD0=1;
         __delay_ms(1000);
        
      //  ret = USART_ReadByteBlocking(&data_resived);
        /*
        ret =  read_button_state(&btn1,&status_btn1);
        ret =  read_button_state(&btn2,&status_btn2);
        ret =  read_button_state(&btn3,&status_btn3);
        ret =  read_button_state(&btn4,&status_btn4);
        if(status_btn1 == BUTTON_PRESSED){
            status_btn1=BUTTON_RELEASED;
            PORTDbits.RD0=1;
            ret = USART_WriteByteBlocking('a');
        }
        if(status_btn2 == BUTTON_PRESSED){
            status_btn2=BUTTON_RELEASED;
            PORTDbits.RD0=0;
            ret = USART_WriteByteBlocking('b');
        }
        if(status_btn3 == BUTTON_PRESSED){
            status_btn3=BUTTON_RELEASED;
            ret = USART_WriteByteBlocking('c');
        }
        if(status_btn4 == BUTTON_PRESSED){
            status_btn4=BUTTON_RELEASED;
            ret = USART_WriteByteBlocking('d');
        }
           */
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


