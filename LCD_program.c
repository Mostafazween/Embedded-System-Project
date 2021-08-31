
/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 14/8/2021 12:30:30 PM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/

#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "power.h"

void LCD_Enable(void)
{
	DIO_WritePin(EN_PORT,EN,1);
	_delay_ms(2);
	DIO_WritePin(EN_PORT,EN,0);
	_delay_ms(2);
}
void LCD_SendCommand(unsigned char cmd)
{
	#if defined eight_bit_mode
	DIO_WritePort(LCD_PORT,cmd);
	DIO_WritePin(RS_PORT,RS,0);
	LCD_Enable();
	#elif defined four_bit_mode
	DIO_WriteLowNibble(LCD_PORT,cmd>>4);
	DIO_WritePin(RS_PORT,RS,0);
	LCD_Enable();
	DIO_WriteLowNibble(LCD_PORT,cmd);
	LCD_Enable();
	#endif
	_delay_ms(1);
}
void LCD_Init(void)
{
	#if defined eight_bit_mode
	_delay_ms(200);
	DIO_SetPortDir(LCD_PORT,1);
	DIO_SetPinDir(EN_PORT,EN,1);
	DIO_SetPinDir(RS_PORT,RS,1);
	DIO_SetPinDir(RW_PORT,RW,1);
	DIO_WritePin(RW_PORT,RW,0);
	LCD_SendCommand(EIGHT_BIT);
	_delay_ms(1);
	LCD_SendCommand(CURSOR_ON_DISPLAY_ON);
	_delay_ms(1);
	LCD_SendCommand(CLR_SCREEN);
	_delay_ms(10);
	LCD_SendCommand(ENTRY_MODE);
	_delay_ms(1);
	#elif defined four_bit_mode
	_delay_ms(200);
	DIO_SetPinDir(LCD_PORT,0,1);
	DIO_SetPinDir(LCD_PORT,1,1);
	DIO_SetPinDir(LCD_PORT,2,1);
	DIO_SetPinDir(LCD_PORT,3,1);
	DIO_SetPinDir(EN_PORT,EN,1);
	DIO_SetPinDir(RS_PORT,RS,1);
	DIO_SetPinDir(RW_PORT,RW,1);
	DIO_WritePin(RW_PORT,RW,0);
	LCD_SendCommand(RETURN_HOME);
	_delay_ms(10);
	LCD_SendCommand(FOUR_BIT);
	_delay_ms(1);
	LCD_SendCommand(CURSOR_ON_DISPLAY_ON);
	_delay_ms(1);
	LCD_SendCommand(CLR_SCREEN);
	_delay_ms(10);
	LCD_SendCommand(ENTRY_MODE);
	_delay_ms(1);
	#endif

}
void LCD_SendChar(unsigned char data)
{
	#if defined eight_bit_mode
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(RS_PORT,RS,1);
	LCD_Enable();
	#elif defined four_bit_mode
	DIO_WriteLowNibble(LCD_PORT,data>>4);
	DIO_WritePin(RS_PORT,RS,1);
	LCD_Enable();
	DIO_WriteLowNibble(LCD_PORT,data);
	LCD_Enable();
	#endif
}
void LCD_SendNumber(unsigned int num)
{
	unsigned char data;
	unsigned int number;
	unsigned char arr[NUMBER_DIGITS];
	signed char i=0;
	signed int count=0;
	if (num!=0)
	{
		while(num!=0)
		{
			number=num%10;
			arr[i]=number;
			i++;
			num=num/10;
			count++;
		}
		for(i=(count-1);i>=0;i--)
		{
			data =0x30+ arr[i];
			LCD_SendChar(data);
		}
	}
	else
	{
		LCD_SendChar(num+48);
	}

}
void LCD_SendFloatingNumber(double num)
{
	int i_part=(int)(num);
	double f_part=num- (double)(i_part);
	LCD_SendNumber(i_part);
	LCD_SendChar('.');
	f_part=f_part*power(10,DIGITS);
	LCD_SendNumber(f_part);
}
void LCD_SendString(char *str)
{
	while((*str)!='\0')
	{
		LCD_SendChar(*str);
		str++;
	}
}
void LCD_ClearScreen(void)
{
	LCD_SendCommand(CLR_SCREEN);
	_delay_ms(10);
}
void LCD_MoveCursor(unsigned char row,unsigned char coloumn)
{
	char cmd=0x80;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		cmd=0x80;
	}
	else if(row==1)
	{
		cmd=0x80+coloumn-1;
	}
	else if(row==2)
	{
		cmd=0xc0+coloumn-1;
	}
	LCD_SendCommand(cmd);
	_delay_ms(1);
}
