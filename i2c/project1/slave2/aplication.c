/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
#define Slave1      0x60
#define Slave2      0x61

mssp_i2c_t i2c_obj;
std_returntype ret = E_OK;
volatile uint8 counter=0;
void I2C_interrupt(){
    counter++;
}
int main(){

    i2c_obj.i2c_cfg.i2c_SMBus_control=I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode=I2C_MSSP_SLAVE_MODE;
    i2c_obj.i2c_cfg.i2c_slew_rate=I2C_SLEW_RATE_DISABLE;
    i2c_obj.i2c_cfg.i2c_slave_address=0X62;
    i2c_obj.i2c_cfg.i2c_mode_cfg=I2C_SLAVE_MODE_7BIT_ADDRESS;
    i2c_obj.I2C_DefaultInterruptHandler=I2C_interrupt;
    i2c_obj.i2c_cfg.i2c_general_call =I2C_GENERAL_CALL_DISABLE;
    ret = MSSP_I2C_Init(&i2c_obj);

    while(1){

      
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


