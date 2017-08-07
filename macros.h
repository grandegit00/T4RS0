#ifndef MACROS_H_
#define MACROS_H_

/******** CONSTANTES Y MACROS **************/
//#define F_CPU             16000000UL

// #define BAUDRATE            4800//9600//38400
// #define BAUD_PRESCALE         ( (F_CPU/16/4800) - 1)

// #define I2C_BAUD           100000UL            // 100khz. Valor por defecto
// #define I2C_BAUD_PRESCALE        ( ( (F_CPU/I2C_BAUD)-16)/2)
 
//#define BASURA              "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

//#define POLY              0x8005 // 0x1D0F //0x8408         // polinomio para calcular CRC16


#define FALSE             0
#define TRUE              1
#define DERECHA             1
#define IZQUIERDA           2
#define BIG_END             1
#define LITTLE_END            2

#define ON                1               // estados para las valvulas
#define OFF               0

#define IN_               1
#define OUT_              0

#define I2C_STOP            1

#define  EEMEM  __attribute__((section(".eeprom")))

//-- macros para manejo de registros y bits
#define BIT_TO_HIGH(REG, BIT)     (REG) |= (1<< (BIT) )
#define BIT_TO_LOW(REG, BIT)      (REG) &= ~(1<< (BIT) )
#define BIT_CONMUTE(REG, BIT)     (REG) ^= (1<< (BIT) )
#define BIT_COMPARE(REG,BIT,COMPI)    ( (REG) & ( (COMPI) << (BIT) ) )// compara un bit de un reg con un valor dado,'1' o '0'

#define REG_SET(REG, VAL)       (REG) = (VAL)

#define BIT_GET(PIN, BIT)       (PIN & (1 << BIT))        // hacemos una mascara, de forma que solo sera >0 si BIT es '1'

//- MAPEO DE PULSADORES in/out
#define PULSE_ON        PA2
#define PULSE_OFF       PA3

#define PULSE3         PA0
#define PULSE4         PA5
#define PULSE5         PA1
#define PULSE6         PB3
#define PULSE7         PB2
#define PULSE8         PA4
#define PULSE9         PB5 //--> Misma función RA3 (5) en 402S, 404S y 406S(off)
#define PULSE10        PB4 //--> Misma función RA3 (5) en 402S, 404S y 406S(off)

#define OUT3            PC5
#define OUT4            PC6
#define OUT5            PC7
#define OUT6            PB0
#define OUT7            PB1
#define OUT8            PC4
#define OUT9            PC5
#define OUT10           PC5



//*****************************************************************************


// POSICIONES MEMORIA EEPROM
#define MEMO_IDENTIFICADOR      100   // 4 BYTES
#define MEMO_RSSI         110   // 2 BYTES
#define MEMO_MATRIZ         150   // 432 BYTES

#define MEMO_STATE          120   // 1 byte
#define MEMO_BUZZER         125   // 1 byte 


// CONSTANTES DEL PROGAMA
#define TIEMPO_FILTRO_MS      10//100   //tiempo necesario para validar un cambio de estado boton, en miliseg
#define TIEMPO_ENVIA_PULSACION    50        //tiempo necesario para crear mensaje desde la primera pulsacion de boton.
#define TIEMPO_ESPERA_PULSA_CONTROL 2000    // Tiempo de espera para considerar que se cambia una funcion con la tecla de control
#define TIEMPO_ESPERA_PROG_ID   10000   // Tiempo de espeera para considerar que se cambia a modo prog ID
//#define TIEMPO_PARPADEO_LED     200
#define NUM_PARPADEOS_LED     12  

#define PROG_ID_REPOSO        1
#define PROG_ID_PREPARADO     2
#define PROG_ID_DUANDO        3

// #define MODO_ACTIVACION_RELES    1
//#define MODO_PROGRAMACION     2

#define N_BOTONES           8 //pause 12   //16 *****
#define N_PULS_CONTROL          2

//#define SEC_DUAL_TX_RX        {1, 2, 1, 2, 1, 2}

// CONSTANTES DE TAMAÑOS