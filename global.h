
#ifndef GLOBAL_H_
#define GLOBAL_H_


struct boton{

  // unsigned  port;
  // unsigned  reg;
  unsigned  actual_state;              // determina el estado estable del boton, ya validado
  unsigned  read_state;             // determina el estado leido, necesita superar el tiempo de filtrado para su validacion
  unsigned  filtering;                // indica que el estado del boton esta pasando el filtro anti rebotes
  uInt16    cont_filter;              // determina el tiempo contado para validar el valor detectado
  
 };

struct Global{

  uInt8       system_state;
  uInt16      cont_valida_pulsado;
  unsigned    validando_pulsado;
  unsigned    envia_pulsacion;
  uInt8       proceso_duando_id;
  unsigned    bandera_change_led;
  
  unsigned    cambia_estado_control;
  uInt16      cont_valida_pulsado_control;
  unsigned    validando_pulsado_control;
  
  unsigned    hay_buzzer;

  //-- BOTONES
  struct      boton array_buttons[8];
  
  //-- PULSADORES DE CONTROL
  struct      boton array_control[2];

};

extern struct Global var_Global;

#endif