/*
 * 4x3 keypad.h
 *
 * author : mostafa gomaa
 */

#include "standard_types.h" 

#include "key_pad_config.h"


/*function to return the pressed key of 4x3 keypad*/
u_int8 pressed_key1(void);

/*function to calculate the pressed number*/
u_int8 adjust_num(u_int8);
