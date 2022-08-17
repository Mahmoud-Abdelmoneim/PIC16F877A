#include "hal_spi.h"
#if SPI_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE  
    void (* SPI_interruptHandler) (void);
#endif 
static void MSSP_SPI_Interrupt_Init(const spi_t *_spi_obj);
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const spi_t *_spi_obj);
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const spi_t *_spi_obj);
static void SPI_Select_Mode(spi_t *_spi_obj);
std_returntype SPI_Init(spi_t *_spi_obj){
    std_returntype ret=E_OK;
    if(NULL==_spi_obj)
        ret=E_NOT_OK;
    else
    {
        SPI_SYNCHRONOUS_SERIAL_PORT(SPI_SYNCHRONOUS_SERIAL_PORT_DISABLE);
        SPI_Select_Mode(_spi_obj); 
        if(_spi_obj->spi_mode == SPI_MASTER_MODE_CLK_TMR2 
                || _spi_obj->spi_mode == SPI_MASTER_MODE_CLK_FOSC_DIV_64 
                || _spi_obj->spi_mode == SPI_MASTER_MODE_CLK_FOSC_DIV_16 
                || _spi_obj->spi_mode == SPI_MASTER_MODE_CLK_FOSC_DIV_4 ){
            
            MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(_spi_obj);
        } 
        if(_spi_obj->spi_mode == SPI_SLAVE_MODE_SS_PIN_DISABLED 
                || _spi_obj->spi_mode == SPI_SLAVE_MODE_SS_PIN_ENABLED){
            
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(_spi_obj);
        }
        SPI_CLOCK_POLARITY_SELECT(_spi_obj->clk_polarity);
        SPI_CLOCK_PHASE_SELECT(_spi_obj->clk_phase);
        SPI_DATA_SAMPLED_SELECT(_spi_obj->data_sampled);
        
#if SPI_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE  
         MSSP_SPI_Interrupt_Init(_spi_obj);
#endif         
        SPI_SYNCHRONOUS_SERIAL_PORT(SPI_SYNCHRONOUS_SERIAL_PORT_ENABLE); 
    }
    return ret;
}
std_returntype SPI_DeInit(spi_t *_spi_obj){
   std_returntype ret=E_OK;
    if(NULL==_spi_obj)
        ret=E_NOT_OK;
    else
    {
        SPI_SYNCHRONOUS_SERIAL_PORT(SPI_SYNCHRONOUS_SERIAL_PORT_DISABLE);
    } 
   return ret;
}

std_returntype SPI_SendByte(spi_t *_spi_obj,uint8 _data){
    std_returntype ret=E_OK;
    if(NULL==_spi_obj)
        ret=E_NOT_OK;
    else
    {
        SSPBUF = _data;
        while(!SSPSTATbits.BF);
        PIR1bits.SSPIF = 0;
    }
    return ret;
}
std_returntype SPI_ReadByte(spi_t *_spi_obj,uint8 *_data){
    std_returntype ret=E_OK;
    if(NULL==_spi_obj || NULL == _data)
        ret=E_NOT_OK;
    else
    {
        while(SSPSTATbits.BF == 0); 
        *_data = SSPBUF;        
    }
    return ret;
}

static void SPI_Select_Mode(spi_t *_spi_obj){
    
     switch(_spi_obj->spi_mode){
            case SPI_SLAVE_MODE_SS_PIN_DISABLED:          
                SPI_SYNCHRONOUS_SELECT_MODE(SPI_SLAVE_MODE_SS_PIN_DISABLED);
                break;
            case SPI_SLAVE_MODE_SS_PIN_ENABLED:
                SPI_SYNCHRONOUS_SELECT_MODE(SPI_SLAVE_MODE_SS_PIN_ENABLED);    
                break;
            case SPI_MASTER_MODE_CLK_TMR2:          
                SPI_SYNCHRONOUS_SELECT_MODE(SPI_MASTER_MODE_CLK_TMR2);
                break;
            case SPI_MASTER_MODE_CLK_FOSC_DIV_64:
                SPI_SYNCHRONOUS_SELECT_MODE(SPI_MASTER_MODE_CLK_FOSC_DIV_64);    
                break;
            case SPI_MASTER_MODE_CLK_FOSC_DIV_16:          
                SPI_SYNCHRONOUS_SELECT_MODE(SPI_MASTER_MODE_CLK_FOSC_DIV_16);
                break;
            case SPI_MASTER_MODE_CLK_FOSC_DIV_4:
                SPI_SYNCHRONOUS_SELECT_MODE(SPI_MASTER_MODE_CLK_FOSC_DIV_4);    
                break;
         default: ;    
     }
}
void SPI_ISR(void){
#if SPI_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE  
        SPI_InterruptFlagClear();
        if(SPI_interruptHandler){
            SPI_interruptHandler();
        }
#endif     
}
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(const spi_t *_spi_obj){
    std_returntype ret=E_OK;
    pin_config_t SPI_SDO = {.port=PORTC_INDEX,.pin=GPIO_PIN5,.direction=GPIO_DIRICTION_OUTPUT};
    pin_config_t SPI_SDI = {.port=PORTC_INDEX,.pin=GPIO_PIN4,.direction=GPIO_DIRICTION_INPUT};
    pin_config_t SPI_CLK = {.port=PORTC_INDEX,.pin=GPIO_PIN3,.direction=GPIO_DIRICTION_OUTPUT};
    
    ret = gpio_pin_diriction_initailize(&SPI_SDO); 
    ret = gpio_pin_diriction_initailize(&SPI_SDI);
    ret = gpio_pin_diriction_initailize(&SPI_CLK);    
    
}
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const spi_t *_spi_obj){
    std_returntype ret = E_NOT_OK;
    ADCON1bits.PCFG=7;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRICTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin = GPIO_PIN4, .direction = GPIO_DIRICTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin = GPIO_PIN3, .direction = GPIO_DIRICTION_INPUT};
    pin_config_t SPI_SS  = {.port = PORTA_INDEX, .pin = GPIO_PIN5, .direction = GPIO_DIRICTION_INPUT};
    
    ret = gpio_pin_diriction_initailize(&SPI_SDO); 
    ret = gpio_pin_diriction_initailize(&SPI_SDI);
    ret = gpio_pin_diriction_initailize(&SPI_CLK); 
    
    if(SPI_SLAVE_MODE_SS_PIN_ENABLED == _spi_obj->spi_mode){
        ret = gpio_pin_diriction_initailize(&SPI_SS);
    }
}

static void MSSP_SPI_Interrupt_Init(const spi_t *_spi_obj){
#if SPI_INTERRUPT_FEATIRE_ENABLE == INTERRUPT_FEATIRE_ENABLE
    INTERRUPT_Golableinterruptenable();
    INTERRUPT_peripheralinterruptenable();
    SPI_InterrupEnable() ;
    SPI_interruptHandler = _spi_obj->SPI_interruptHandler;
#endif     
}