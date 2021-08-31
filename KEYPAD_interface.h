/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 21/8/2021 08:14:30 PM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_
void          KEYPAD_Init (void);
unsigned char KEYPAD_Press(void);
#define NOTPRESSED 0XFF
#endif /* KEYPAD_INTERFACE_H_ */