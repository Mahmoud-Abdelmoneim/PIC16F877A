#include "ecu_lcd_char.h"

static std_returntype lcd_4bit_send(const char_4bit_lcd_t *_lcd,uint8 comand);
static std_returntype lcd_4bit_send_enable_signal(const char_4bit_lcd_t *_lcd);
static std_returntype lcd_8bit_send_enable_signal(const char_8bit_lcd_t *_lcd);
static std_returntype lcd_8bit_set_cursor(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column);
static std_returntype lcd_4bit_set_cursor(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column);
/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_4bit_initialize(const char_4bit_lcd_t *_lcd){
    std_returntype ret= E_NOT_OK;
    uint8 counter = ZERO_INT;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
          ret = gpio_pin_initailize(&(_lcd->lcd_rs)); 
          ret = gpio_pin_initailize(&(_lcd->lcd_en));
          for(counter=0;counter<4;counter++){
              ret = gpio_pin_initailize(&(_lcd->lcd_data[counter]));
          }
          __delay_ms(20);
          ret = lcd_4bit_send_comand(_lcd,_LCD_8BIT_MODE_2_LINE);
          __delay_ms(5);
          ret = lcd_4bit_send_comand(_lcd,_LCD_8BIT_MODE_2_LINE);
          __delay_us(150);
          ret = lcd_4bit_send_comand(_lcd,_LCD_8BIT_MODE_2_LINE);
          
          ret = lcd_4bit_send_comand(_lcd,_LCD_CLEAR);
          ret = lcd_4bit_send_comand(_lcd,_LCD_RETURN_HOME);
          ret = lcd_4bit_send_comand(_lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
          ret = lcd_4bit_send_comand(_lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
          ret = lcd_4bit_send_comand(_lcd,_LCD_4BIT_MODE_2_LINE);
          ret = lcd_4bit_send_comand(_lcd,0x80);          
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_4bit_send_comand(const char_4bit_lcd_t *_lcd,uint8 comand){
    std_returntype ret= E_NOT_OK;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs),GPIO_LOW);
        ret = lcd_4bit_send(_lcd,comand >> 4);
        ret = lcd_4bit_send_enable_signal(_lcd);
        ret = lcd_4bit_send(_lcd,comand);   
        ret = lcd_4bit_send_enable_signal(_lcd);
    }
    return ret;
}
/**
 * 
 * @param lcd Pointer to the LCD configurations
 * @param data The data that we need to send to the LCD
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_4bit_send_char_data(const char_4bit_lcd_t *_lcd,uint8 data){
    std_returntype ret= E_NOT_OK;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(_lcd->lcd_rs),GPIO_HIGH);
        ret = lcd_4bit_send(_lcd,data >> 4);
        ret = lcd_4bit_send_enable_signal(_lcd);
        ret = lcd_4bit_send(_lcd,data);   
        ret = lcd_4bit_send_enable_signal(_lcd);
            
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_4bit_send_char_data_pos(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column ,uint8 data){
    std_returntype ret= E_NOT_OK;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(_lcd,row,column);
        ret = lcd_4bit_send_char_data(_lcd,data); 
            
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_4bit_send_string(const char_4bit_lcd_t *_lcd,uint8 *str){
    std_returntype ret= E_NOT_OK;
    if(NULL==_lcd || str == NULL){     
            ret=E_NOT_OK;
    }
    else{
        while(*str){
            ret = lcd_4bit_send_char_data(_lcd,*str++);
        }
            
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_4bit_send_string_pos(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column,uint8 *str){
    std_returntype ret= E_NOT_OK;
    if(NULL==_lcd || str == NULL){     
            ret=E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(_lcd,row,column);
        ret = lcd_4bit_send_string(_lcd,str);
            
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_4bit_send_custom_char(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column,
                                         const uint8* _char[],uint8 mem_pos){
    std_returntype ret= E_NOT_OK;
    uint8 lcd_counter=0;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_comand(_lcd,(_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter =0;lcd_counter <= 7;lcd_counter++){
            ret = lcd_4bit_send_char_data(_lcd,_char[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(_lcd,row,column,mem_pos);           
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_8bit_initialize(const char_8bit_lcd_t *_lcd){
    std_returntype ret= E_NOT_OK;
    uint8 counter=ZERO_INT;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
          ret = gpio_pin_initailize(&(_lcd->lcd_rs)); 
          ret = gpio_pin_initailize(&(_lcd->lcd_en));
          for(counter=0;counter<8;counter++){
              ret = gpio_pin_initailize(&(_lcd->lcd_data[counter]));
          }
          __delay_ms(20);
          ret = lcd_8bit_send_comand(_lcd,_LCD_8BIT_MODE_2_LINE);
          __delay_ms(5);
          ret = lcd_8bit_send_comand(_lcd,_LCD_8BIT_MODE_2_LINE);
          __delay_us(150);
          ret = lcd_8bit_send_comand(_lcd,_LCD_8BIT_MODE_2_LINE);
          
          ret = lcd_8bit_send_comand(_lcd,_LCD_CLEAR);
          ret = lcd_8bit_send_comand(_lcd,_LCD_RETURN_HOME);
          ret = lcd_8bit_send_comand(_lcd,_LCD_ENTRY_MODE_INC_SHIFT_OFF);
          ret = lcd_8bit_send_comand(_lcd,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
          ret = lcd_8bit_send_comand(_lcd,_LCD_8BIT_MODE_2_LINE);
          ret = lcd_8bit_send_comand(_lcd,0x80);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_8bit_send_comand(const char_8bit_lcd_t *_lcd,uint8 comand){
    std_returntype ret= E_NOT_OK;
    uint8 counter = ZERO_INT;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
            ret = gpio_pin_write_logic(&(_lcd->lcd_rs),GPIO_LOW);
            for(counter=0;counter<8;++counter){
                ret = gpio_pin_write_logic(&(_lcd->lcd_data[counter]),(comand >> counter) & (uint8)0x01);
            }
            ret = lcd_8bit_send_enable_signal(_lcd);
        
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_8bit_send_char_data(const char_8bit_lcd_t *_lcd,uint8 data){
    std_returntype ret= E_NOT_OK;
    uint8 counter = ZERO_INT;    
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
            ret = gpio_pin_write_logic(&(_lcd->lcd_rs),GPIO_HIGH);
            for(counter=0;counter<8;++counter){
                ret = gpio_pin_write_logic(&(_lcd->lcd_data[counter]),(data >> counter) & (uint8)0x01);
            }
            ret = lcd_8bit_send_enable_signal(_lcd);            
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_8bit_send_char_data_pos(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column ,uint8 data){
    std_returntype ret= E_NOT_OK;
    uint8 counter=ZERO_INT;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
            ret = lcd_8bit_set_cursor(_lcd,row,column);
            ret = lcd_8bit_send_char_data(_lcd,data);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_8bit_send_string(const char_8bit_lcd_t *_lcd,uint8 *str){
    std_returntype ret= E_NOT_OK;
    if(NULL==_lcd || str == NULL){     
            ret=E_NOT_OK;
    }
    else{
        while(*str){
           ret = lcd_8bit_send_char_data(_lcd,*str);
           str++;
        }     
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_8bit_send_string_pos(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column,uint8 *str){
    std_returntype ret= E_NOT_OK;
    if(NULL==_lcd || str == NULL){     
            ret=E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(_lcd,row,column);
        ret = lcd_8bit_send_string(_lcd,str);    
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype lcd_8bit_send_custom_char(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column,
                                         const uint8* _char[],uint8 mem_pos){
    std_returntype ret= E_NOT_OK;
    uint8 lcd_counter=ZERO_INT;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
        ret = lcd_8bit_send_comand(_lcd,(_LCD_CGRAM_START + (mem_pos*8)));
        for(lcd_counter =0;lcd_counter <= 7;lcd_counter++){
            ret = lcd_8bit_send_char_data(_lcd,_char[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(_lcd,row,column,mem_pos);
    }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype convert_uint8_to_string(uint8 value, uint8 *str){
    std_returntype ret= E_NOT_OK;
    if(NULL==str){     
            ret=E_NOT_OK;
    }
    else{
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
            
    }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype convert_uint16_to_string(uint16 value, uint8 *str){
    std_returntype ret= E_NOT_OK;
    if(NULL==str){     
            ret=E_NOT_OK;
    }
    else{
        memset(str, '\0', 6);
        sprintf(str, "%i", value);    
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
std_returntype convert_uint32_to_string(uint32 value, uint8 *str){
    std_returntype ret= E_NOT_OK;
    if(NULL==str){     
            ret=E_NOT_OK;
    }
    else{
        memset(str, '\0', 11);
        sprintf(str, "%i", value);    
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param _data_command
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_returntype lcd_4bit_send(const char_4bit_lcd_t *_lcd,uint8 _data_comand){
    std_returntype ret= E_NOT_OK;
   
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{   
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[0]),(_data_comand >> 0) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[1]),(_data_comand >> 1) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[2]),(_data_comand >> 2) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd->lcd_data[3]),(_data_comand >> 3) & (uint8)0x01);
        
    } 
    return ret;
}
/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_returntype lcd_4bit_send_enable_signal(const char_4bit_lcd_t *_lcd){
    std_returntype ret= E_NOT_OK;
   
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{   
        ret = gpio_pin_write_logic(&(_lcd->lcd_en),GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(_lcd->lcd_en),GPIO_LOW);
    } 
    return ret;
}

/**
 * 
 * @param lcd
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_returntype lcd_8bit_send_enable_signal(const char_8bit_lcd_t *_lcd){
    std_returntype ret= E_NOT_OK;
   
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{   
        ret = gpio_pin_write_logic(&(_lcd->lcd_en),GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(_lcd->lcd_en),GPIO_LOW);
    } 
    return ret;
}

/**
 * 
 * @param lcd Pointer to the LCD configuration parameters defined by the user
 * @param row Which row you need to print your character
 * @param coulmn Which column you need to print your character
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_returntype lcd_8bit_set_cursor(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column){
    std_returntype ret= E_NOT_OK;
    column--;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
        switch(row){
            case ROW1:ret = lcd_8bit_send_comand(_lcd,(0x80 + column)); break;
            case ROW2:ret = lcd_8bit_send_comand(_lcd,(0xc0 + column)); break;
            case ROW3:ret = lcd_8bit_send_comand(_lcd,(0x94 + column)); break;
            case ROW4:ret = lcd_8bit_send_comand(_lcd,(0xd4 + column)); break;
            default:;
        }
        
    } 
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param coulmn
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static std_returntype lcd_4bit_set_cursor(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column){
    std_returntype ret= E_NOT_OK;
    column--;
    if(NULL==_lcd){     
            ret=E_NOT_OK;
    }
    else{
        switch(row){
            case ROW1:ret = lcd_4bit_send_comand(_lcd,(0x80 + column)); break;
            case ROW2:ret = lcd_4bit_send_comand(_lcd,(0xc0 + column)); break;
            case ROW3:ret = lcd_4bit_send_comand(_lcd,(0x94 + column)); break;
            case ROW4:ret = lcd_4bit_send_comand(_lcd,(0xd4 + column)); break;
            default:;
        }
        
    } 
    return ret;
}

