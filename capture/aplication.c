/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
volatile uint8 flag=0;
void tmr(void);
timer1_t timer_obj={
    .TIMER1_InterruptHandler=tmr,
    .timer1_mode=TIMER1_TIMER_MODE,
    .timer1_osc_cfg=RIMER1_OCS_ENABLE,
    .timer1_preload_value=0,
    .perscaler_value=TIMER1_PRESCALER_DIV_BY_1,
    
};
void CCP(void){
    flag++;
    static uint16 vlue=0;
    if(flag==1)
        Timer1_Write_Value(&timer_obj,0);
    else if(flag==2){
        flag=0;
        CCP1_Capture_Mode_Read_Value(&vlue);
        
    }
}
void tmr(void){
    //flag2++;
}

ccp_t ccp_obj;

std_returntype ret=E_NOT_OK; 
int main() {
    
    ccp_obj.CCP1_InterruptHandler=CCP;
    ccp_obj.ccp_inst=CCP1_INST;
    ccp_obj.ccp_mode=CCP_CAPTURE_MODE_SELECTED;
    ccp_obj.ccp_mode_variant=CCP_CAPTURE_MODE_1_RISING_EDGE;
    ccp_obj.ccp_pin.port=PORTC_INDEX;
    ccp_obj.ccp_pin.pin=GPIO_PIN2;
    ccp_obj.ccp_pin.direction=GPIO_DIRICTION_INPUT;
    ret = CCP_Init(&ccp_obj);
    ret = Timer1_Init(&timer_obj);
    
    while(1)
    {
        
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


