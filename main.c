#include <pic16F18854.h>

#include "tipos.h"
#include "macros.h"
#include "global.h"
#include "config_system.h"


void DELAY_ms(unsigned int ms_Count)
{
    uInt8 i,j;
    
    for(i = 0; i< ms_Count; i ++)
    {
        for(j = 0; j < 1000; j ++);
    }
}

int main() 
{

    //- main bucle
    while(1)
    {
        PORTA = 0xff; /* Turn ON all the leds connected to Ports */
        PORTB = 0xff;
        PORTC = 0xff;
        PORTD = 0xff;
        DELAY_ms(100);
        
        PORTA = 0x00; /* Turn OFF all the leds connected to Ports */
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;
        DELAY_ms(100);
    }

    return (0);
}