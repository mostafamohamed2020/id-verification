/*
 * ID_VERIFICATION.c
 * THIS CODE CHECK THE EXISTENCE OF AN ID
 * Created: 9/23/2020 1:38:48 AM
 * Author: mostafa gomaa
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>      /*included for malloc function*/
#define F_CPU 1000000UL /*controller frequency*/

/*including lcd header file*/
#include "my_lcd.h"
/*including keypad header file*/
#include "4x3_keypad.h"
/*including standard typed header file*/
#include "standard_types.h"

/*function to enroll new ID*/
void enroll_id(void);  /*function prototype*/

/*function to search for ID*/
void check_existence(void);  /*function prototype*/

/*struct for node*/
struct node {
	u_int32 data; /*integer value*/
	struct node *next; /*pointer to the next node*/
};

struct node *head = NULL; /*creating the head*/

int main(void)
{
	DDRB &= (~(1<<PB0)); /*starting switch as input*/
	
	while (PINB & (1<<PB0)); /*start when the button pressed*/
	{
		_delay_ms(100); 
		lcd_init(); /*initialization the LCD module*/
		lcd_display_strindinlocation(1,0,"ID verification"); /*prompt sentences*/
	    lcd_display_strindinlocation(2,0,"PRESS EITHER 1 OR 2");
	    lcd_display_strindinlocation(3,0,"1 TO ENROLL NEW ID");
	    lcd_display_strindinlocation(4,0,"2 TO CHECK EXISTENCE"); 
		while(1)
    {
			if (pressed_key1() == 1)
		{
			 _delay_ms(1000);
	         lcd_clear_screen();
	         enroll_id();
		}
		else if (pressed_key1() == 2)
		{
			 _delay_ms(1000);
	         lcd_clear_screen();
	         check_existence();
		}/*end of else if*/
	}/*end of while(1)*/
	}/*end of while (pressed button)*/	
 }/*end of main */
 
/*enroll_id function implementation*/
void enroll_id(void)
{
	u_int8 i , num; 
	u_int32 ID = 1000 , NUM;
	u_int8 id[1][4];  /*the token ID from LCD*/
	struct node *temp = (struct node *) malloc(sizeof(struct node)); /*creating node to hold the data*/
	if (temp == NULL )  /*check if the allocation done properly*/
	{ 
		lcd_display_strindinlocation(2,1,"allocation failed"); 
		return;
	}
	lcd_display_strindinlocation(1,1,"ENROLL THE ID");
	lcd_gotorowcolumn(2,4);
	for (i=0;i<4;i++)
	{
		num = pressed_key1();
		id[0][i] = num;  /*storing the ID in succession*/
		_delay_ms(200);
		lcd_inttostr(id[0][i]); /*converting the token number*/
		NUM += (num * ID);    /*evaluating the integer value*/
		ID  = ID/ 10;
	}
	temp->next = head; /*temp points to head*/
	temp->data = NUM; /*storing data*/
	head = temp; /*temp points to the added node*/ 
	_delay_ms(200);
	lcd_display_strindinlocation(3,0,"ID STORED SUCCEFULLY"); /*verification message*/
}
/*check_existence function implementation*/
void check_existence(void)
{
	u_int8 i , num; 
	u_int32 ID = 1000 , NUM;
	u_int8 id[1][4];  /*the token ID from LCD*/
	struct node *sp = head;
	if (head == NULL) /*check if there is no enrolled ID*/
	{
		lcd_clear_screen();
		lcd_display_strindinlocation(2,2,"NO EXISTED IDS");
		lcd_display_strindinlocation(3,2,"ENROLL ID FIRSTLY");
		return;
	}
	lcd_display_strindinlocation(1,1,"ENTER THE ID");
	lcd_gotorowcolumn(2,2);
	for (i=0;i<4;i++)
	{
		num = pressed_key1();
		id[0][i] = num;  /*storing the ID in succession*/
		_delay_ms(200);
		lcd_inttostr(id[0][i]); /*converting the token number*/
		NUM += (num * ID);    /*evaluating the integer value*/
		ID  = ID/ 10;
	}
	_delay_ms(200);
	for (sp ; sp != NULL ; sp = sp->next) /*search for the ID*/
	{
		if (sp->data == NUM)
		{
			lcd_clear_screen();
			_delay_ms(200);
			lcd_display_strindinlocation(2,2,"ID EXISTED");
			return;
		}
	} /*end of loop*/
	   lcd_clear_screen();
	   _delay_ms(200);
	   lcd_display_strindinlocation(2,2,"ID NOT EXISTED !");
} /*end of function*/