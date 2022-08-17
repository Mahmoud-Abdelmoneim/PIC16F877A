#include "hal_i2c.h"
static inline void I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t *i2c_obj);
static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t *i2c_obj);
static inline void MSSP_I2C_Mode_GPIO_CFG();
static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t *i2c_obj);

#if MSSP_I2C_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
static void (*I2C_Report_Write_Collision_InterruptHandler)(void) = NULL;
static void (*I2C_DefaultInterruptHandle)(void) = NULL;
static void (*I2C_Report_Receive_Overflow_InterruptHandle)(void) = NULL;
#endif
/**
 * 
 * @param i2c_obj
 * @return 
 */
std_returntype MSSP_I2C_Init(const mssp_i2c_t *i2c_obj){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj)
        ret=E_NOT_OK;
    else
    {
        //disable the MSSP module
        MSSP_MODULE_DISABLE_CFG();
        //i2c selct mode
        if(I2C_MSSP_MASTER_MODE == i2c_obj->i2c_cfg.i2c_mode ){
            I2C_Master_Mode_Clock_Configurations(i2c_obj);
        }
        else if(I2C_MSSP_SLAVE_MODE == i2c_obj->i2c_cfg.i2c_mode){
            
            //enable or disable general call
            if(I2C_GENERAL_CALL_ENABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_ENABLE_CFG();
            }
            else if(I2C_GENERAL_CALL_DISABLE == i2c_obj->i2c_cfg.i2c_general_call){
                I2C_GENERAL_CALL_DISABLE_CFG();
            }
            else{/*Nothing*/}
            //Release the clock
            SSPCONbits.CKP = 1;
            //No collision 
            SSPCONbits.WCOL = 0;
            //No overflow
            SSPCONbits.SSPOV = 0;
            
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
            I2C_Slave_Mode_Configurations(i2c_obj);  
        }
        else{/*Nothing*/}
        //config RC3 & RC4 as INPUT
        MSSP_I2C_Mode_GPIO_CFG();
        
        if(I2C_SLEW_RATE_ENABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
            I2C_SLEW_RATE_ENABLE_CFG();
        }
        else if(I2C_SLEW_RATE_DISABLE == i2c_obj->i2c_cfg.i2c_slew_rate){
            I2C_SLEW_RATE_DISABLE_CFG();
        }
        else{/*Nothing*/}
        
        if(I2C_SMBus_ENABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
            I2C_SMBus_ENABLE_CFG();
        }
        else if(I2C_SMBus_DISABLE == i2c_obj->i2c_cfg.i2c_SMBus_control){
            I2C_SMBus_DISABLE_CFG();
        }
        else{/*Nothing*/}
        
        
#if MSSP_I2C_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE        
        MSSP_I2C_Interrupt_Configurations(i2c_obj);
#endif
        MSSP_MODULE_ENABLE_CFG();
        
        
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @return 
 */
std_returntype MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj)
        ret=E_NOT_OK;
    else
    {
        MSSP_MODULE_DISABLE_CFG(); 
#if MSSP_I2C_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE        
        MSSP_I2C_InterruptDisable();
        MSSP_I2C_BUS_COL_InterruptDisable();
#endif
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @return 
 */
std_returntype MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj)
        ret=E_NOT_OK;
    else
    {
        SSPCON2bits.SEN = 1;

        while(SSPCON2bits.SEN);
        
        PIR1bits.SSPIF = 0;
        if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
            ret = E_OK; /* Indicates that a Start bit has been detected last */
        }
        else{
            ret = E_NOT_OK; /* Start bit was not detected last */
        }
        
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @return 
 */
std_returntype MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj)
        ret=E_NOT_OK;
    else
    {
        SSPCON2bits.RSEN = 1;
        
        while(SSPCON2bits.RSEN);
        
        PIR1bits.SSPIF = 0;
               
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @return 
 */
std_returntype MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj)
        ret=E_NOT_OK;
    else
    {
        SSPCON2bits.PEN = 1;
        
        while(SSPCON2bits.PEN);
        
        PIR1bits.SSPIF = 0;
        if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P){
            ret = E_OK; /* Indicates that a Start bit has been detected last */
        }
        else{
            ret = E_NOT_OK; /* Start bit was not detected last */
        }
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @param i2c_data
 * @param _ack
 * @return 
 */
std_returntype MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj || _ack == NULL)
        ret=E_NOT_OK;
    else
    {
        SSPBUF = i2c_data;
        
        while(SSPSTATbits.BF);
        
        PIR1bits.SSPIF = 0;
        
        if(I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT){
             *_ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        }
        else if(I2C_ACK_NOT_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT){
             *_ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
            
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @param ack
 * @param i2c_data
 * @return 
 */

std_returntype MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj || i2c_data == NULL)
        ret=E_NOT_OK;
    else
    {
        I2C_MASTER_RECEIVE_DISABLE_CFG();
        
        while(!SSPSTATbits.BF);
        
        *i2c_data = SSPBUF;
        if(I2C_MASTER_SEND_ACK == ack){
            SSPCON2bits.ACKDT = 0;
            SSPCON2bits.ACKEN = 1;
        }
            
        else if (I2C_MASTER_SEND_NACK == ack){
            SSPCON2bits.ACKDT = 1;
            SSPCON2bits.ACKEN = 1;
        }
        else {/*nothing*/}
            
            
        
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @param i2c_data
 * @param _ack
 * @return 
 */

std_returntype MSSP_I2C_Master_Write_NBlocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *_ack){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj || _ack == NULL)
        ret=E_NOT_OK;
    else
    {
        
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 * @param ack
 * @param i2c_data
 * @return 
 */
std_returntype MSSP_I2C_Master_Read_NBlocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data){
    std_returntype ret=E_OK;
    if(NULL==i2c_obj || i2c_data == NULL)
        ret=E_NOT_OK;
    else
    {
        
    }
    return ret;
}
/**
 * 
 * @param i2c_obj
 */
static inline void I2C_Master_Mode_Clock_Configurations(const mssp_i2c_t *i2c_obj){
    SSPCONbits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg;
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / i2c_obj->i2c_clock) - 1);
}
/**
 * 
 * @param i2c_obj
 */
static inline void I2C_Slave_Mode_Configurations(const mssp_i2c_t *i2c_obj){
    SSPCONbits.SSPM = i2c_obj->i2c_cfg.i2c_mode_cfg; 
}

 
static inline void MSSP_I2C_Mode_GPIO_CFG(){
    std_returntype ret=E_OK;
    
    pin_config_t SPI_SDA = {.port=PORTC_INDEX,.pin=GPIO_PIN4,.direction=GPIO_DIRICTION_INPUT};
    pin_config_t SPI_CLK = {.port=PORTC_INDEX,.pin=GPIO_PIN3,.direction=GPIO_DIRICTION_INPUT};
     
    ret = gpio_pin_diriction_initailize(&SPI_SDA);
    ret = gpio_pin_diriction_initailize(&SPI_CLK); 
}
/**
 * 
 * @param i2c_obj
 */
static inline void MSSP_I2C_Interrupt_Configurations(const mssp_i2c_t *i2c_obj){
#if MSSP_I2C_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
    MSSP_I2C_InterrupEnable() ;
    MSSP_I2C_BUS_COL_InterruptDEnable() ;
    MSSP_I2C_InterruptFlagClear() ;
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    I2C_Report_Write_Collision_InterruptHandler = i2c_obj->I2C_Report_Write_Collision;
    I2C_DefaultInterruptHandle = i2c_obj->I2C_DefaultInterruptHandler;
    I2C_Report_Receive_Overflow_InterruptHandle = i2c_obj->I2C_Report_Receive_Overflow;
    INTERRUPT_Golableinterruptenable();
    INTERRUPT_peripheralinterruptenable();
#endif    
}
#if MSSP_I2C_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
void I2C_ISR(){
    MSSP_I2C_InterruptFlagClear() ;
    if(I2C_DefaultInterruptHandle)
        I2C_DefaultInterruptHandle();
}

void I2C_BC_ISR(){
    MSSP_I2C_BUS_COL_InterruptFlagClear();
    if(I2C_Report_Write_Collision_InterruptHandler)
        I2C_Report_Write_Collision_InterruptHandler();
}
#endif