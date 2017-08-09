
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

void init_system(void)
{
  init_registers();
  init_inputs();


  var_Global.system_state = OFF; //EEPROM_read_byte(add_state);
  
  if(var_Global.init_state != OFF && var_Global.init_state != ON)
    var_Global.init_state = OFF;

  

}

/**
 * Init register state
 * { item_description }
 **/
void init_registers()
{
  //PORTX &= ~(1<<PX0);  //bit in register to '0'
  //PORTX |= (1<<PX1);   //bit in register to '1'

    //- PORTA all IN but PA7 OUT
  TRISA = 0x7F;
 ;

  //- PORTC all OUT
  TRISC = 0x00;

  //- PORTB IN & OUT
  TRISB = 0x3C;

  //- Set Ini STATE for OUTPUT --> '0'
  PORTC = 0x00;   // - all output LOW

  PORTB & = ~(1<<PB0);
  PORTB & = ~(1<<PB1);
  PORTB & = ~(1<<PB6);
  PORTB & = ~(1<<PB7);
}

/**
 * @brief      { function_description }
 * Init the inputs structs
 */
void init_inputs()
{
  for(uInt8 i = 0; i < 8; i ++)
  {
    // switch(i)
    // {
    //   case 0:
    //   case 1:
    //   case 2:
    //   case 5:
    //     var_Global.array_buttons[i].reg = PORTA;
    //     break;

    //   case 3:
    //   case 4:
    //   case 6:
    //   case 7:
    //     var_Global.array_buttons[i].reg = PORTB;
    //     break;
    // }

    var_Global.array_buttons[i].actual_state = OFF;
    var_Global.array_buttons[i].read_state = OFF;
    var_Global.array_buttons[i].filtering = OFF;
    var_Global.array_buttons[i].cont_filter = 0;
    
    if(i == 0 || i == 1)
    {
      var_Global.array_control[i].actual_state = OFF;
      var_Global.array_control[i].read_state = OFF;
      var_Global.array_control[i].filtering = OFF;
      var_Global.array_control[i].cont_filter = 0;
    }
  }

  // var_Global.array_control[0].reg = PORTA;
  // var_Global.array_control[1].reg = PORTA;
}

/**
 * { item_description }
 * Logic control when the Tx is ON
 */
void system_ON_logic()
{
  
  if(BIT_COMPARE(PORTA, PULSE_OFF, ON))  // pulsado botton de Off
  {
    var_Global.array_control[1].read_state = TRUE;    // load value
    
    if(var_Global.array_control[1].actual_state != var_Global.array_control[1].read_state = TRUE)
    {
      var_Global.array_control[1].actual_state = var_Global.array_control[1].read_state;
      var_Global.array_control[1].filtering = TRUE;
      var_Global.array_control[1].cont_filter = 0;

    }

    if(var_Global.array_control[1].cont_filter >= T_VALID_GOTO_OFF)
    {
      var_Global.array_control[1].filtering = FALSE;
      var_Global.array_control[1].cont_filter = 0;
      var_Global.system_state = OFF;
      EPROM_write_byte(add_state, var_Global.system_state);
      BIT_TO_HIGH(PORTC, LED_RED);

    }
  }

  if(BIT_COMPARE(PORTA, PULSE3, ON))
  {
    // vamos por esta lógica
  }
}
 /**
 * { item_description }
 * Logic control when the Tx is OFF
 */
 void system_OFF_logic()
{

}
