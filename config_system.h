#ifndef CONFIG_SYSTEM_H_
#define CONFIG_SYSTEM_H_

#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
 
#define _XTAL_FREQ 4000000  //cristal utilizado de 4Mhz
 
/**
       - RA0 (2) Pulsador 3 --> RC5 (16) Salida
       - RA5 (7) Pulsador 4 --> RC6 (17) Salida 
       - RA1 (3) Pulsador 5 --> RC7 (18) Salida 
       - RB3 (24) Pulsador 6 --> RB0 (21) Salida 
       - RB2 (23) Pulsador 7 --> RB1 (22) Salida
       - RA4 (6) Pulsador 8 --> RC4 (15) Salida
       - RB5 (26) Pulsador 9 --> Misma función que RA3 (5) en 402S, 404S y 406S
       - RB4 (25) Pulsador 10 --> Misma función que RA3 (5) en 402S, 404S y 406S

 */

// //- PORTA all IN
// TRISA = 0xFF;

// //- PORTC all OUT
// TRISC = 0x00;

// //- PORTB IN & OUT
// TRISB = 0x3C;

// //- Set Ini STATE for OUTPUT --> '0'
// PORTC = 0x00;   // - all output LOW

// PORTB & = ~(1<<PB0);
// PORTB & = ~(1<<PB1);
// PORTB & = ~(1<<PB6);
// PORTB & = ~(1<<PB7);


#endif