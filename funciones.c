
// #include <avr/io.h>
// #include <util/delay.h>
#include <stdio.h>
// #include <avr/interrupt.h>


#include "tipos.h"
#include "macros.h"
#include "global.h"
#include "funciones.h"
#include "config_system.h"


/**
 * @brief      { function_description }
 * system init, var and registers
 */

void init(void)
{
  g_estado_actual = OFF; //EEPROM_read_byte(add_state);
  if(g_estado_actual != OFF && g_estado_actual != ON)
    g_estado_actual = OFF;



}