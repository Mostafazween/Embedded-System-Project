/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 25/8/2021 11:14:30 AM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "EEPROM_interface.h"                
#define Default_DATA 0XFF   //default data
#define EEPROM_STATUS 0X20  //location of default data
/*location of data for EEPROM*/
#define EEPROM_LOC1 0X21
#define EEPROM_LOC2 0X22
#define EEPROM_LOC3 0X23
#define EEPROM_LOC4 0X24
#define  NUM_TRIES 3   //number of tries
unsigned char arr[4];  //password digits
int main(void)
{
	LCD_Init();     //initiate LCD
    KEYPAD_Init();  // initiate Keypad
	unsigned char value=Default_DATA;  
	unsigned char i,flag=0,tries=NUM_TRIES;
	/*set password of the safe*/
		if (EEPROM_Read(EEPROM_STATUS)==Default_DATA)
		{
			LCD_SendString("set pass:");
			for(i=0;i<4;i++)
			{
				do
				{
					value=KEYPAD_Press();
				}
				while(value==Default_DATA);
				LCD_SendChar(value);
				_delay_ms(500);
				LCD_MoveCursor(1,10+i);
				LCD_SendChar('*');
				EEPROM_Write(EEPROM_LOC1+i,value);
				_delay_ms(1000);
			}
			EEPROM_Write(EEPROM_STATUS,0X00);
		}
		while(flag==0) //just password flag=1 true don't check again
		{
			LCD_ClearScreen();
			LCD_SendString("check:");
			for(i=0;i<4;i++)
			{
				do
				{
					arr[i]=KEYPAD_Press();
				}
				while(arr[i]==Default_DATA);
				LCD_SendChar(arr[i]);
				_delay_ms(500);
				LCD_MoveCursor(1,7+i);
				LCD_SendChar('*');
				_delay_ms(500);
			}
			if(EEPROM_Read(EEPROM_LOC1)==arr[0]&&EEPROM_Read(EEPROM_LOC2)==arr[1]&&EEPROM_Read(EEPROM_LOC3)==arr[2]&&EEPROM_Read(EEPROM_LOC4)==arr[3])
			{
				LCD_ClearScreen();
				LCD_SendString("right pass");
				LCD_MoveCursor(2,1);
				LCD_SendString("safe opened");
				_delay_ms(1000);
				LCD_ClearScreen();
				flag=1;
			}
			else
			{
				tries--;
				if(tries>0)
				{
					LCD_ClearScreen();
					LCD_SendString("wrong pass");
					_delay_ms(500);
					LCD_MoveCursor(2,1);
					LCD_SendString("left tries:");
					LCD_SendNumber(tries);
					_delay_ms(500);
				}
				else
				{
					LCD_ClearScreen();
					LCD_SendString("wrong pass");
					LCD_MoveCursor(2,1);
					LCD_SendString("safe closed");
					_delay_ms(1000);
					LCD_ClearScreen();
					flag=1;
				}
			}
		}
}

