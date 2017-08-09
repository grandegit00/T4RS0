#ifndef EEPROM_H_
#define EEPROM_H_


//** Lee/Escribe en EEPROM
void          eepromWrite(char *data, uint8_t tam_data, uint32_t dir);
char          *eepromRead(uint8_t tam_data, uint32_t dir);

void          EEPROM_write_byte(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read_byte(unsigned int uiAddress);
void          EEPROM_write_N_bytes(unsigned int uiAddress, char *cadena, uInt8 n_bytes);
unsigned char *EEPROM_read_N_bytes(unsigned int uiAddress, uInt8 n_bytes);


#endif /* EEPROM_H_ */