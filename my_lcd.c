/*
 * lcd module .c
 * author : mostafa gomaa
 */

/*including common macros geader file*/
#include "common_macros.h"

/*including standard types header file*/
#include "standard_types.h"

/*including lcd.h header file*/
#include "my_lcd.h"

/*including avr/io library*/
#include <avr/io.h>

/*including delay header file*/
#include <util/delay.h>

/*function to initialize the LCD module*/
void lcd_init(void)
{
	lcd_data_direction = 0xFF; /*all data pins are output pins*/
	lcd_control_direction |= ((1<<E) | (1<<RS) | (1<<RW));   /*all control pins are output pins*/
	lcd_sendcommand(two_line_eight_bit); /*determine the 2 lines and 5x8 matrix*/
	lcd_sendcommand(cursor_off);   /*disable the cursor*/
	lcd_sendcommand(clear_screen); /*clear the screen at the beginning*/ 
	
}

/*function to send a specific command to LCD*/
void lcd_sendcommand(u_int8 command)
{
	clear_bit(lcd_control_port,RS);  /*instruction mode RS =0*/
	/*the same as lcd_control_port &= (~(1<<RS)); */
	
	clear_bit(lcd_control_port,RW); /*write data to lcd so RW =0*/
	/*the same as lcd_control_port &= (~(1<<RW));*/
	
	_delay_ms(1);
	set_bit(lcd_control_port,E);  /*enabling E pin*/
	_delay_ms(1);
	lcd_data_port = command ;  /*store the hex value of commend*/
	_delay_ms(1);
	clear_bit(lcd_control_port,E); /*disable E pin after sending the command*/
	_delay_ms(1);
}

/*function to display character*/
void lcd_displaycharacter(u_int8 character)
{
	set_bit(lcd_control_port,RS); /*data mode RS=1*/
	clear_bit(lcd_control_port,RW); /*write data to LCD so RW =0*/
	_delay_ms(1);
	set_bit(lcd_control_port,E); /*enable E pin*/
	_delay_ms(1);
   lcd_data_port = character ; /*store the hex value of character*/
   _delay_ms(1);
   clear_bit(lcd_control_port,E); /*disable the E pin*/
   _delay_ms(1);
}

/*function to display a string*/
void lcd_displaystring(const char *str)
{
	u_int8 i=0;
	while(str[i] != '\0')
	{
		lcd_displaycharacter(str[i]); /*print each character in succession*/
		i++;
	}
}

/*function to go to a specific point in the LCD*/
void lcd_gotorowcolumn(u_int8 row,u_int8 column)
{
	u_int8 address;
	switch (row)
	{
		case 1:
		   address = column ;
		   break;
		case 2:
		   address = column + 0x40;
		   break;
		case 3:
		   address = column + 0x14;
		   break;
		case 4:
		address = column + 0x54;
		break;
	}
	lcd_sendcommand(address | set_cursor_location); /*adding address to the beginning of the LCD*/
}

/*function to display a string from a specific location*/
void lcd_display_strindinlocation(u_int8 row,u_int8 column,const char *str)
{
	lcd_gotorowcolumn( row, column); /*go to the specific location*/
	lcd_displaystring(str);  /*display the string*/
	
}

/*function to display a character at specific location*/
void lcd_displaycharacterat(u_int8 row,u_int8 column,u_int8 character)
{
	lcd_gotorowcolumn(row,column);  /*go to th location*/
	lcd_displaycharacter(character); /*display the character*/
}

/*function to clear the screen*/
void lcd_clear_screen(void)
{
	lcd_sendcommand(clear_screen); /*send a command to clear the LCD*/
}

/*function to display an integer value*/
void lcd_inttostr(unsigned int data)
{
	char buff[20];  /*string to hold the data*/
	itoa(data,buff,10); /* 10 means decimal*/
	lcd_displaystring(buff);
}