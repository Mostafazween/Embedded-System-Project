/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 31/7/2021 07:14:30 AM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/
#ifndef STD_MACRO_BIT_H_
#define STD_MACRO_BIT_H_
#define register_size 8
#define set_bit(reg,bit) reg|=(1<<bit)
#define clear_bit(reg,bit) reg&=~(1<<bit)
#define toggle_bit(reg,bit) reg^=(1<<bit)
#define read_bit(reg,bit) ((reg&(1<<bit))>>bit)
#define IS_set_bit(reg,bit) ((reg&((1<<bit))>>bit))
#define IS_clear_set_bit(reg,bit) !((reg&(1<<bit))>>bit))
#define rol_bit(reg,bit) reg=(reg<<bit)|(reg>>(register_size-bit))
#define ror_bit(reg,bit) reg=(reg>>bit)|(reg<<(register_size-bit))
#endif /* STD_MACRO_BIT_H_ */