
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


  var_Global.system_state = EEPROM_read_byte(add_state);
  var_Global.led_write_on = OFF;
  
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
  for(uInt8 i = 0; i < N_BOTONES; i ++)
  {
    switch(i)
    {
      case 0:
      case 1:
      case 2:
      case 5:
        var_Global.array_buttons[i].reg = PORTA;
        break;

      case 3:
      case 4:
      case 6:
      case 7:
        var_Global.array_buttons[i].reg = PORTB;
        break;
    }

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

  var_Global.array_buttons[0].port = PA0;
  var_Global.array_buttons[1].port = PA5;
  var_Global.array_buttons[2].port = PA1;

  var_Global.array_buttons[3].port = PB3;
  var_Global.array_buttons[4].port = PB2;

  var_Global.array_buttons[5].port = PA4;

  var_Global.array_buttons[6].port = PB5;
  var_Global.array_buttons[7].port = PB4;

  // var_Global.array_control[0].reg = PORTA;
  // var_Global.array_control[1].reg = PORTA;
}
/**
 * @brief      { function_description }
 * Init the inputs structs
 */
void init_ouput()
{
  for(uInt8 i = 0; i < N_BOTONES; i ++)
  {
    switch(i)
    {
      case 0:
      case 1:
      case 2:
      case 5:
      case 6:
      case 7:
        var_Global.array_outputs[i].reg = PORTC;
        break;

      case 3:
      case 4:
        var_Global.array_outputss[i].reg = PORTB;
        break;
    }
  }
  array_outputs[0].port = PC5;
  array_outputs[0].port = PC6;
  array_outputs[0].port = PC7;

  array_outputs[0].port = PB0;
  array_outputs[0].port = PB1;

  array_outputs[0].port = PC4;
  // array_outputs[0].port = PC5;
  // array_outputs[0].port = PC5;
}
/**
 * { item_description }
 * Logic control when the Tx is ON
 */
void system_ON_logic()
{
  //- Estado guardado ON, se pulsa OFF
  if(BIT_COMPARE(PORTA, PULSE_OFF, ON))  // pulsado botton de Off
  {
    var_Global.array_control[1].read_state = TRUE;    // load value
    
    if(var_Global.array_control[1].actual_state != var_Global.array_control[1].read_state)
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
      
      //- keep state
      EPROM_write_byte(add_state, var_Global.system_state);
      //- LED RED --> ON
      BIT_TO_HIGH(PORTC, LED_RED);

      while(1);
    }
  }

  for(uInt8 i = 0; i < N_BOTONES; i ++)
  {
    if(BIT_COMPARE(array_buttons[i].reg, array_buttons[i].port, ON))
    {
      var_Global.array_buttons[i].read_state = TRUE;

      if(var_Global.array_buttons[i].actual_state != var_Global.array_buttons[i].read_state)
      {
        var_Global.array_buttons[i].actual_state = var_Global.array_buttons[i].read_state;
        var_Global.array_buttons[i].filtering = TRUE;
        var_Global.array_buttons[i].cont_filter = 0;
      }

      if(var_Global.array_buttons[i].cont_filter != T_VALID_PULSE_F)
      {
        var_Global.array_buttons[i].filtering = FALSE;
        var_Global.array_buttons[i].cont_filter = 0;

        //- OUPUT Activate 
        BIT_TO_HIGH(array_outputs[i].reg, array_outputs[i].port);
        //- POWER Activate (Low Level)
        BIT_TO_LOW(PORTA, POWER_ENCODER);
        //- LED White 
        //-TODO cambiar esto por la activacion de la bandera "led_white_on" para
        //en el timer empezar a contar el tiempo de parpadeo 600ms on/off, el 
        //cambio se hara en la rutina de interrupción del timer. Ahora se activa
        //fijo el LED_WHITE para probar.
        //-----------var_Global.led_white_on = TRUE;
        BIT_TO_HIGH(PORTC, LED_WHITE);


        while(1);

      }
    }
  }

  
  
}
 /**
 * { item_description }
 * Logic control when the Tx is OFF
 */
 void system_OFF_logic()
{
  if(BIT_COMPARE(PORTA, PULSE_ON, ON))
  {
    var_Global.array_control[0].read_state = TRUE; 

    if(var_Global.array_control[0].actual_state != var_Global.array_control[0].read_state)
    {
      var_Global.array_control[0].actual_state = var_Global.array_control[0].read_state;
      var_Global.array_control[0].filtering = TRUE;
      var_Global.array_control[0].cont_filter = 0;
      //-TODO quitar la activacion fija de led y activar la bandera de contador
      //- var_Global.led_red_on_off = TRUE;
      //
       
      BIT_TO_HIGH(PORTC, LED_RED);
    }

    if(var_Global.array_control[0].cont_filter >= T_VALID_GOTO_ON)
    {
      //TODO
      BIT_TO_LOW(PORTC, LED_RED); //var_Global.led_red_on_off = OFF;
      
      var_Global.system_state = ON;

      EPROM_write_byte(add_state, var_Global.system_state);

      BIT_TO_HIGH(PORTC, LED_WHITE);

    }
  }

  for(uInt8 i = 0; i < N_BOTONES; i ++)
  {
    if(BIT_COMPARE(array_buttons[i].reg, array_buttons[i].port, ON))
    {
      var_Global.array_buttons[i].read_state = TRUE;

      if(var_Global.array_buttons[i].actual_state != var_Global.array_buttons[i].read_state)
      {
        var_Global.array_buttons[i].actual_state = var_Global.array_buttons[i].read_state;
        var_Global.array_buttons[i].filtering = TRUE;
        var_Global.array_buttons[i].cont_filter = 0;
      }

      if(var_Global.array_buttons[i].cont_filter != T_VALID_PULSE_F)
      {
        var_Global.array_buttons[i].filtering = FALSE;
        var_Global.array_buttons[i].cont_filter = 0;

        
        //- LED red
        //-TODO cambiar esto por la activacion de la bandera "led_red_on_off" para
        //en el timer empezar a contar el tiempo de parpadeo 600ms on/off, el 
        //cambio se hara en la rutina de interrupción del timer. Ahora se activa
        //fijo el LED_RED para probar.
        //-----------var_Global.led_red_on_off = TRUE;
        BIT_TO_HIGH(PORTC, LED_RED);


        while(1);

      }
    }


}
