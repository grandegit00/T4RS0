#include <pic16F18854.h>

#include "tipos.h"
#include "macros.h"
#include "global.h"
#include "config_system.h"
#include "eeprom.h"
#include "funciones.h"


void DELAY_ms(unsigned int ms_Count)
{
    uInt8 i,j;
    
    for(i = 0; i< ms_Count; i ++)
    {
        for(j = 0; j < 1000; j ++);
    }
}

//- TODO TODO
//confibgurar los TIMER para las especificaciones de tiempo 
//cambiar la activacion fija de LED por la activacion de banderas de contadores
//en los timers sera donde se aumenten los contadores siempre y cuando las
//banderas de "filtering" de cada puerto esten activas

int main() 
{
  //- here the system state is read from EEPROM
  init_system();
  
  //- main bucle
  while(1)
  {
    /*
    //--- TEST TEST TEST--------------------
    PORTA = 0xff; // Turn ON all the leds connected to Ports 
    PORTB = 0xff;
    PORTC = 0xff;
    PORTD = 0xff;
    DELAY_ms(100);

    PORTA = 0x00; // Turn OFF all the leds connected to Ports 
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    DELAY_ms(100);
    //--- TEST TEST TEST--------------------
  */
    //- System is ON
    if(var_Global.system_state) 
    {
      system_ON_logic();
    }
    else // SYTEM is OFF
    {
      system_OFF_logic();
    }


  }




  return (0);
}
/**
 * @brief      
 * 
 * TIMER Para 1 segundo
 * 
 * { function_description }
 */
void timer1seg()
{
  for(uInt8 i = 0; i < N_BOTONES; i ++)
  {
    if(var_Global.array_buttons[i].filtering)
      var_Global.array_buttons[i].cont_filter ++;
  }

  for(uInt8 i = 0; i < 2; i ++)
  {
    if(var_Global.array_control[i].filtering)
      var_Global.array_control[i].cont_filter ++;
  }
}