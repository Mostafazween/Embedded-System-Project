
/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 07/8/2021 08:14:30 PM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/
#include "EEPROM_private.h"
void EEPROM_Write(const unsigned short address, const unsigned char data)
{
	EEARL=(unsigned char)address;
	EEARH=(unsigned char)address>>8;
	EEDR=data;
	EECR|=(1<<EEMWE);                            
	EECR|=(1<<EEWE);                              
	while(((EECR&(1<<EEWE))>>EEWE)==1);           
}
unsigned char EEPROM_Read(const unsigned short address)
{
	EEARL=(unsigned char)address;
	EEARH=(unsigned char)address>>8;
	EECR|=(1<<EERE);                              
	return EEDR;
}