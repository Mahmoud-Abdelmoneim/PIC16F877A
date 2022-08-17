/* 
 * File:   ecu_lcd_char.h
 * Author: El-Wattaneya
 *
 * Created on 12 ?????, 2022, 03:19 ?
 */

#ifndef ECU_LCD_CHAR_H
#define	ECU_LCD_CHAR_H
#define _XTAL_FREQ 4000000
/*........section include.........*/
#include "../../MCAL_layer/GPIO/hal_gpio.h"

/*........section: macro declarations......... */
#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0x02
#define _LCD_ENTRY_MODE_DEC_SHIFT_OFF   0x04
#define _LCD_ENTRY_MODE_DEC_SHIFT_ON    0x05
#define _LCD_ENTRY_MODE_INC_SHIFT_OFF   0x06
#define _LCD_ENTRY_MODE_INC_SHIFT_ON    0x07
#define _LCD_CURSOR_MOVE_SHIFT_LEFT     0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT    0x14
#define _LCD_DISPLAY_SHIFT_LEFT         0x18
#define _LCD_DISPLAY_SHIFT_RIGHT        0x1C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF 0x0C
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON  0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF  0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON   0x0F
#define _LCD_DISPLAY_OFF_CURSOR_OFF              0x08
#define _LCD_8BIT_MODE_2_LINE           0x38
#define _LCD_4BIT_MODE_2_LINE           0x28

#define _LCD_CGRAM_START                0x40
#define _LCD_DDRAM_START                0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4


/*........section: macro function declarations......... */


/*........section: data type declarations......... */

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];

}char_4bit_lcd_t;

typedef struct{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];

}char_8bit_lcd_t;
/*........section: function declarations......... */
std_returntype lcd_4bit_initialize(const char_4bit_lcd_t *_lcd);
std_returntype lcd_4bit_send_comand(const char_4bit_lcd_t *_lcd,uint8 comand);
std_returntype lcd_4bit_send_char_data(const char_4bit_lcd_t *_lcd,uint8 data);
std_returntype lcd_4bit_send_char_data_pos(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column ,uint8 data);
std_returntype lcd_4bit_send_string(const char_4bit_lcd_t *_lcd,uint8 *str);
std_returntype lcd_4bit_send_string_pos(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column,uint8 *str);
std_returntype lcd_4bit_send_custom_char(const char_4bit_lcd_t *_lcd,uint8 row,uint8 column,
                                         const uint8* _char[],uint8 mem_pos);

std_returntype lcd_8bit_initialize(const char_8bit_lcd_t *_lcd);
std_returntype lcd_8bit_send_comand(const char_8bit_lcd_t *_lcd,uint8 comand);
std_returntype lcd_8bit_send_char_data(const char_8bit_lcd_t *_lcd,uint8 data);
std_returntype lcd_8bit_send_char_data_pos(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column ,uint8 data);
std_returntype lcd_8bit_send_string(const char_8bit_lcd_t *_lcd,uint8 *str);
std_returntype lcd_8bit_send_string_pos(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column,uint8 *str);
std_returntype lcd_8bit_send_custom_char(const char_8bit_lcd_t *_lcd,uint8 row,uint8 column,
                                         const uint8* _char[],uint8 mem_pos);

std_returntype convert_uint8_to_string(uint8 value, uint8 *str);
std_returntype convert_uint16_to_string(uint16 value, uint8 *str);
std_returntype convert_uint32_to_string(uint32 value, uint8 *str);
#endif	/* ECU_LCD_CHAR_H */

