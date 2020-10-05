#ifndef COMMON_MACROS_H_INCLUDED
#define COMMON_MACROS_H_INCLUDED
/*macro to set a specific bit*/
#define set_bit(byte,bit_num) (byte |= (1<<bit_num))
/*macro to clear a specific bit*/
#define clear_bit(byte,bit_num) (byte &= (~(1<<bit_num)))
/*macro to toggle a specific bit*/
#define toggle_bit(byte,bit_num) (byte ^= (1<<bit_num))
/*macro to check if a bit is set*/
#define bit_is_set(byte,bit_num) (byte & (1<<bit_num))
/*macro to check if bit is cleared*/
#define bit_is_clear(byte,bit_num) (!(byte & (1<<bit_num)))
/*macro to perform right circular*/
#define cir_right(byte,bits) (byte = (byte >> bits) | (byte << (8-bits)))
/*macro to perform left circular*/
#define cir_left(byte,bits) (byte = (byte << bits) | (byte >> (8-bits)))
/*macro to display a specific flag*/
#define show_flag(byte,flag_num) (byte = (byte >> flag_num) | (1))




#endif // COMMON_MACROS_H_INCLUDED
