/* 
 * LCD_module.h
 * author : mostafa gomaa
 */

/*including AVR\IO library*/
#include <avr/io.h>

/*including standard types geader file*/
#include "standard_types.h"

/* 
 * configuratoin of lcd
 * lcd data pins will be conected to PORT C
 * lcd control pins will be connected to PORTD
 */
#define RS PD4
#define E PD5
#define RW PD6
#define lcd_data_direction DDRC
#define lcd_data_port PORTC
#define lcd_control_direction DDRD
#define lcd_control_port PORTD

/*lcd commands*/
#define clear_screen 0x01
#define two_line_eight_bit 0x38
#define cursor_on 0x0C
#define cursor_off 0x0E
#define set_cursor_location 0x80

/*lcd functions prototype*/
void lcd_init(void);
void lcd_sendcommand(u_int8 command);
void lcd_displaycharacter(u_int8 character);
void lcd_displaystring(const char *str);
void lcd_gotorowcolumn(u_int8 row,u_int8 column);
void lcd_display_strindinlocation(u_int8 row,u_int8 column,const char *str);
void lcd_clear_screen(void);
void lcd_displaycharacterat(u_int8 row,u_int8 column,u_int8 character);
void lcd_inttostr(unsigned int data);


 