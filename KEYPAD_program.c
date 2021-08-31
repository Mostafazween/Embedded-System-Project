/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 21/8/2021 08:14:30 PM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/

#include "DIO_interface.h"
#include "KEYPAD_config.h" 
#include "KEYPAD_interface.h" 
void KEYPAD_Init(void)
{
	DIO_SetPinDir     (KEYPAD_PORT,0,1);
	DIO_SetPinDir     (KEYPAD_PORT,1,1);
	DIO_SetPinDir     (KEYPAD_PORT,2,1);
	DIO_SetPinDir     (KEYPAD_PORT,3,1);
	DIO_SetPinDir     (KEYPAD_PORT,4,0);
	DIO_SetPinDir     (KEYPAD_PORT,5,0);
	DIO_SetPinDir     (KEYPAD_PORT,6,0);
	DIO_SetPinDir     (KEYPAD_PORT,7,0);
	DIO_EnablePullUp  (KEYPAD_PORT,4,1);
	DIO_EnablePullUp  (KEYPAD_PORT,5,1);
	DIO_EnablePullUp(KEYPAD_PORT,6,1);
	DIO_EnablePullUp(KEYPAD_PORT,7,1);
}
unsigned char KEYPAD_Press(void)
{
	unsigned char arr[4][4]={{'7','8','9','/'},
	                         {'4','5','6','*'},
							 {'1','2','3','-'},
							 {'c','0','=','+'}};
	unsigned char row,column,state;
	unsigned char return_val=NOTPRESSED;
	for(row=0;row<4;row++)
	{
		DIO_WritePin(KEYPAD_PORT,0,1);
		DIO_WritePin(KEYPAD_PORT,1,1);
		DIO_WritePin(KEYPAD_PORT,2,1);
		DIO_WritePin(KEYPAD_PORT,3,1);
		DIO_WritePin(KEYPAD_PORT,row,0);
		for(column=0;column<4;column++)
		{
			state=DIO_ReadPin(KEYPAD_PORT,(column+4));
			if(state==0)
			{
				return_val=arr[row][column];
				break;
			}
		}
			if (state==0)
			{
				break; 
			}
	}	
	return return_val;						 
}