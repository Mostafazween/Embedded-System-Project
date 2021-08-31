/**********************************************************************************************/
/* Author       : Mostafa Zween                                                               */
/* Date         : 07/8/2021 08:14:30 PM                                                       */
/* version      : 01                                                                          */
/**********************************************************************************************/


   
#ifndef EEPROM_PRIVATE_H_
#define EEPROM_PRIVATE_H_

#define   EERIE  3
#define   EEMWE  2
#define   EEWE   1
#define   EERE   0

        /*       REGISTERS ADDRESSES FOR EEPROM        */
		
#define  EEAR                  *((volatile unsigned short*)(0x003E))
#define  EEARH                 *((volatile unsigned char*)(0x003F))
#define  EEARL                 *((volatile unsigned char*)(0x003E)) 
#define  EEDR                  *((volatile unsigned char*)(0x003D))
#define  EECR                  *((volatile unsigned char*)(0x003C))
#endif 
