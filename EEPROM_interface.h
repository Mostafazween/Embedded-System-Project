/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 07/8/2021 08:14:30 PM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
void EEPROM_Write(const unsigned short address, const unsigned char data);
unsigned char EEPROM_Read(const unsigned short address);
#endif /* EEPROM_INTERFACE_H_ */
