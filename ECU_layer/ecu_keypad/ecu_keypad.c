/* 
 * File:   ecu_keypad.c
 * Author: El-Wattaneya
 *
 * Created on 25 ?????, 2022, 08:16 ?
 * 
 * 
 */
#include "ecu_keypad.h"


static const uint8 btn_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                                        {'7', '8', '9', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'}
                                                                     };

/**
 * @brief Initialize the keypad assigned pins
 * @param _keypad_obj pointer to the keypad configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */

std_returntype keypad_intialize(const keypad_t* _keypad)
{
    std_returntype ret=E_OK;
    uint8 rows_counter=ZERO_INT,columns_counter=ZERO_INT;
    if(NULL==_keypad )
        {
            ret=E_NOT_OK;
        }
    
    else 
        {
            for(rows_counter=ZERO_INT;rows_counter<ECU_KEYPAD_ROWS;rows_counter++)
                {
                    ret = gpio_pin_initailize(&(_keypad->keypad_row_pin[rows_counter]));
                }
            
            for(columns_counter=ZERO_INT;columns_counter<ECU_KEYPAD_COLUMNS;columns_counter++)
                {
                    ret = gpio_pin_diriction_initailize(&(_keypad->keypad_column_pin[columns_counter]));
                }
        }

    return ret;
}
/**
 * @brief Get the value of the button pressed by the user and performing the scanning algorithm
 * @param _keypad_obj pointer to the keypad configurations
 * @param value Value of the button pressed by the user
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
std_returntype keypad_get_value(const keypad_t* _keypad, uint8 * value)
{
    std_returntype ret=E_OK;
    uint8 l_rows_counter=ZERO_INT,l_columns_counter=ZERO_INT,rows_counter=ZERO_INT;
    logic_t column_logic=GPIO_LOW;

    if(NULL==_keypad || value==NULL)
        {
            ret=E_NOT_OK;
        }
    
    else 
        {
            for(l_rows_counter=ZERO_INT;l_rows_counter<ECU_KEYPAD_ROWS;l_rows_counter++)
                {
                    for(rows_counter=ZERO_INT;rows_counter<ECU_KEYPAD_ROWS;rows_counter++)
                         {
                            gpio_pin_write_logic(&(_keypad->keypad_row_pin[rows_counter]),GPIO_LOW);

                         }
                    gpio_pin_write_logic(&(_keypad->keypad_row_pin[l_rows_counter]),GPIO_HIGH);
                        
                    for(l_columns_counter=ZERO_INT;l_columns_counter<ECU_KEYPAD_COLUMNS;l_columns_counter++)
                        {
                           ret = gpio_pin_read_logic(&(_keypad->keypad_column_pin[l_columns_counter]),&column_logic);
                           if(column_logic==GPIO_HIGH)
                           {
                              *value=btn_values[l_rows_counter][l_columns_counter]; 
                           }
                        }
                    
                }
        }

    return ret;


}