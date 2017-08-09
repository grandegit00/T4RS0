
// #include <avr/io.h>
// #include <util/delay.h>
#include <stdio.h>
// #include <avr/interrupt.h>


#include "tipos.h"
#include "macros.h"
#include "global.h"
#include "funciones.h"
#include "eeprom.h"
//***************************************************
//** Escritura en EEPROM                      
//** Param: datos a escribir, tamaños de los datos, dir de MEMO donde se escribiran los datos
//***************************************************
void eepromWrite(char *data, uInt8 tam_data, uInt32 dir)
{
  uInt16 i = 0;
  uInt32 inicio_copi = dir;

  eeprom_busy_wait();
  
  while(i < tam_data)
  {
    eeprom_write_byte( (inicio_copi + i), data[i]);
    i++;
  }  
}

//***************************************************
//** Lectura en EEPROM                      
//** Return: puntero a los datos leidos
//** Param: tamaño de los datos a leer y dir de memo 
//***************************************************
char *eepromRead(uInt8 tam_data, uInt32 dir)
{
  char data_read[tam_data];
  uInt16 i = 0;
  uInt32 inicio_copi = dir;
  
  eeprom_busy_wait();

  for(i=0; i < tam_data; i++)
    data_read[i] = eeprom_read_byte(inicio_copi + i);
  
  return data_read; 
}
//*********************************************************************
//************ FUNCAIONES DE LECTURA PROPIAS *****************

//******************************************************
//** EEPROM WRITE BYTE segun datasheet
//******************************************************
void EEPROM_write_byte(unsigned int uiAddress, unsigned char ucData)
{
  /* Wait for completion of previous write */
  while(EECR & (1<<EEWE));
  
  /* Set up address and data registers */
  EEAR = uiAddress;
  EEDR = ucData;
  
  /* Write logical one to EEMWE */
  EECR |= (1<<EEMWE);
  
  /* Start eeprom write by setting EEWE */
  EECR |= (1<<EEWE);
}
//******************************************************
//** EEPROM READ BYTE segun datasheet
//******************************************************
unsigned char EEPROM_read_byte(unsigned int uiAddress)
{
  /* Wait for completion of previous write */
  while(EECR & (1<<EEWE));
  
  /* Set up address register */
  EEAR = uiAddress;
  
  /* Start eeprom read by writing EERE */
  EECR |= (1<<EERE);
  
  /* Return data from data register */
  return EEDR;
}

//*************************************************
//** EEPROM WRITE N BYTES
//*************************************************
// void EEPROM_write_N_bytes(unsigned int uiAddress, char *cadena, uInt8 n_bytes)
// {
//  for(uInt8 i = 0; i < n_bytes; i ++)
//    EEPROM_write_byte(uiAddress + i, cadena[i]);
// }

//*************************************************
//** EEPROM READ N BYTES
//*************************************************
// unsigned char *EEPROM_read_N_bytes(unsigned int uiAddress, uInt8 n_bytes)
// {
//  unsigned char leida[10];
//  
//  for(uInt8 i = 0; i < n_bytes; i ++)
//    leida[i] = EEPROM_read_byte(uiAddress + i);
//    
//    
//  return leida; 
// }