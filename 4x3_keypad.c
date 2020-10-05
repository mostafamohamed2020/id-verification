/*
 * 4x3 keypad .c
 * the keypad will be connected to port A
 * 
 * author : mostafa gomaa
 */

/*including common macros header file*/
#include "common_macros.h"

/*including standard types header file*/
#include "standard_types.h"

/*including heypad header file*/
#include "4x3_keypad.h"

#include "key_pad_config.h"
#include <avr/io.h>


/* declaration of 4x3 pressed_key function
 * this function takes no arguments and returns the value of key*/
u_int8 pressed_key1(void)
{
	
    u_int8 rows,columns;
    while(1)
    {
        /*first loop will be for columns to set one column as low and the rest
        *stay as high impedance state
        *rows will be connected to the first four pins of portA as inputs
        *columns will be connected to the last four pins of portA in the high impedance mode
        */
        for(columns=0; columns<3; columns++) /*loop of columns*/
        {
           key_pad_DDR = (0b00010000 << columns); /*set the first column as output*/

            key_pad_port = (~(0b00010000 << columns)); /*enable pullups for input pins and set the column to low*/

            for(rows=0; rows<4; rows++) /*loop of rows*/
            {
                if(bit_is_clear(key_pad_IN,rows))
                    return adjust_num((rows * 3)+columns+1);

            } /*end of rows loop*/

        } /*end of columns loop*/

    } /*end of while loop*/

}  /*end of pressed_key function*/

u_int8 adjust_num(u_int8 button)
{
    switch(button)
    {
    
    case 11:
        return 0;
        break;
    default :
        return button;
        break;


    } /*end of switch */
} /*end of function*/

