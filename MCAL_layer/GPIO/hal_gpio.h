/* 
 * File:   hal_gpio.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 , 2022, 02:41 
 */


#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*........section include.........*/
#include "../pic16f877a.h"
#include "../mcal_std_types.h"
#include "../../device_config.h"
#include "hal_gpio_cfg.h"

/*........section: macro declarations......... */


#define MASK_BIT     (uint8)1

#define PORT_PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER     5

#define PORT_MASK          0xFF


/*........section: macro function declarations......... */

#define HWREG(_X)      (*((volatile uint8 *)(_X)))

#define SET_BIT(REG,PIT_POSN)        (REG|=(MASK_BIT << PIT_POSN))
#define CLEAR_BIT(REG,PIT_POSN)      (REG&=~(MASK_BIT << PIT_POSN))
#define TOGGLE_BIT(REG,PIT_POSN)     (REG^=(MASK_BIT << PIT_POSN))
#define READ_BIT(REG,PIT_POSN)       ((REG >> PIT_POSN) & MASK_BIT)

/*........section: data type declarations......... */
typedef enum {
    GPIO_LOW=0,
    GPIO_HIGH
}logic_t;

typedef enum {
    GPIO_DIRICTION_OUTPUT=0,
    GPIO_DIRICTION_INPUT
}direction_t;

typedef enum {
    GPIO_PIN0=0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,        
    GPIO_PIN7        
                     
}pin_index_t;

typedef enum {
    PORTA_INDEX=0,
    PORTB_INDEX,        
    PORTC_INDEX,        
    PORTD_INDEX,        
    PORTE_INDEX,       
}port_index_t;

typedef struct{
    
    uint8 port      :3;           //@ref port_index_t
    uint8 pin       :3;          //@ref pin_index_t
    uint8 direction :1;         //@ref direction_t
    uint8 logic     :1;        //@ref logic_t
    
}pin_config_t;


/*........section: function declarations......... */

std_returntype gpio_pin_diriction_initailize(const pin_config_t * _pin_config);
std_returntype gpio_pin_get_diriction(const pin_config_t * _pin_config,direction_t * dic_status);
std_returntype gpio_pin_write_logic(const pin_config_t * _pin_config,logic_t logic);
std_returntype gpio_pin_read_logic(const pin_config_t * _pin_config,logic_t * logic);
std_returntype gpio_pin_toggle_logic(const pin_config_t * _pin_config);
std_returntype gpio_pin_initailize(const pin_config_t * _pin_config);

std_returntype gpio_port_diriction_initailize(port_index_t port,uint8 dirction);
std_returntype gpio_port_get_diriction(port_index_t port,uint8 * direction_status);
std_returntype gpio_port_write_logic(port_index_t port,uint8 logic);
std_returntype gpio_port_read_logic(port_index_t port,uint8 * logic);
std_returntype gpio_port_toggle_logic(port_index_t port);



#endif	/* HAL_GPIO_H */

