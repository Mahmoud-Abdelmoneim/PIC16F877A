/* 
 * File:   aplication.c
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 ?????, 2022, 10:34 ?
 */


#include "application.h"
#define Slave1      0x60
#define Slave2      0x62
uint8 akn=0;
mssp_i2c_t i2c_obj;
std_returntype ret = E_OK;
void MSSP_I2C_Send_1Byte(uint8 data,uint8 address){
        ret = MSSP_I2C_Master_Send_Start(&i2c_obj);

        ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj,address,&akn); 
        ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj,data,&akn); 
        
        ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}


int main(){

    i2c_obj.i2c_cfg.i2c_SMBus_control=I2C_SMBus_DISABLE;
    i2c_obj.i2c_cfg.i2c_mode=I2C_MSSP_MASTER_MODE;
    i2c_obj.i2c_cfg.i2c_slew_rate=I2C_SLEW_RATE_DISABLE;
    i2c_obj.i2c_clock=100000;
    i2c_obj.i2c_cfg.i2c_mode_cfg=I2C_MASTER_MODE_DEFINED_CLOCK;
    ret = MSSP_I2C_Init(&i2c_obj);

    while(1){

        MSSP_I2C_Send_1Byte('a',Slave1);
        __delay_ms(1000);
        MSSP_I2C_Send_1Byte('b',Slave2);
        __delay_ms(1000);
        MSSP_I2C_Send_1Byte('c',Slave1);
        __delay_ms(1000);
        MSSP_I2C_Send_1Byte('d',Slave2);
        __delay_ms(1000);     
        


      
    }
         
    return (EXIT_SUCCESS);
}

void application_intialize(void)
{
    std_returntype ret=E_NOT_OK;
    // ecu_layer_intialize();
 
}


