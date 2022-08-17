/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
 uint8 data_read=0;
std_returntype ret = E_OK;
led_t led1={.port_name=PORTB_INDEX,.pin=GPIO_PIN0,.led_status=LED_OFF};
led_t led2={.port_name=PORTB_INDEX,.pin=GPIO_PIN1,.led_status=LED_OFF};
led_t led3={.port_name=PORTB_INDEX,.pin=GPIO_PIN2,.led_status=LED_OFF};
led_t led4={.port_name=PORTB_INDEX,.pin=GPIO_PIN3,.led_status=LED_OFF};
void Usart_rx();
car_t car={
  
    .motor_right_up.dc_motor_pin[0].port=PORTB_INDEX,
    .motor_right_up.dc_motor_pin[0].pin=GPIO_PIN0,
    .motor_right_up.dc_motor_pin[0].direction=GPIO_DIRICTION_OUTPUT,
    .motor_right_up.dc_motor_pin[0].logic=GPIO_LOW,
    .motor_right_up.dc_motor_pin[1].port=PORTB_INDEX,
    .motor_right_up.dc_motor_pin[1].pin=GPIO_PIN1,
    .motor_right_up.dc_motor_pin[1].direction=GPIO_DIRICTION_OUTPUT,
    .motor_right_up.dc_motor_pin[1].logic=GPIO_LOW,
    
    
    .motor_lift_up.dc_motor_pin[0].port=PORTB_INDEX,
    .motor_lift_up.dc_motor_pin[0].pin=GPIO_PIN2,
    .motor_lift_up.dc_motor_pin[0].direction=GPIO_DIRICTION_OUTPUT,
    .motor_lift_up.dc_motor_pin[0].logic=GPIO_LOW,
    .motor_lift_up.dc_motor_pin[1].port=PORTB_INDEX,
    .motor_lift_up.dc_motor_pin[1].pin=GPIO_PIN3,
    .motor_lift_up.dc_motor_pin[1].direction=GPIO_DIRICTION_OUTPUT,
    .motor_lift_up.dc_motor_pin[1].logic=GPIO_LOW,    
        
    
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
    usart_obj.USART_RxDefaulteinterruptHandler=Usart_rx;
    usart_obj.USART_TxDefaulteinterruptHandler=NULL;
    ret = USART_ASYNC_Init(&usart_obj);
}
void Usart_rx()
{
    ret = USART_ReadByteBlocking(&data_read);
}





int main(){
    usart_init();
    Car_Init(&car); 
    while(1){
        
        switch(data_read)
        {
            case 'F':
                Car_Move_Forward(&car);
                //__delay_ms(250);
                //data_read=0;
                break;
            case 'B':
                Car_Move_Backword(&car);
                //__delay_ms(250);
                //data_read=0;
                break;
            case 'R':
                Car_Move_Right(&car);
                //__delay_ms(250);
                //data_read=0;
                break;
            case 'L':
                Car_Move_Lift(&car);
                //__delay_ms(250);
                //data_read=0;
                break;
            default:{Car_Stop(&car);}
                
        }
            
      //data_read=0;
     // __delay_ms(50);
    }
         
    return (EXIT_SUCCESS);
}

void Car_Init(car_t *_car){
    ret = dc_motor_intialize(&(_car->motor_lift_up));
    ret = dc_motor_intialize(&(_car->motor_right_up));    
}


void Car_Move_Forward(car_t *_car){
    ret = dc_motor_move_right(&(_car->motor_lift_up));
    ret = dc_motor_move_right(&(_car->motor_right_up));
}
void Car_Move_Backword(car_t *_car){
    ret = dc_motor_move_left(&(_car->motor_lift_up));
    ret = dc_motor_move_left(&(_car->motor_right_up));    
}
void Car_Move_Right(car_t *_car){
    ret = dc_motor_move_right(&(_car->motor_lift_up));
    ret = dc_motor_move_left(&(_car->motor_right_up)); 
}
void Car_Move_Lift(car_t *_car){
    ret = dc_motor_move_left(&(_car->motor_lift_up));
    ret = dc_motor_move_right(&(_car->motor_right_up));    
}
void Car_Stop(car_t *_car){
    ret = dc_motor_stop(&(_car->motor_lift_up));
    ret = dc_motor_stop(&(_car->motor_right_up));  
}



void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


