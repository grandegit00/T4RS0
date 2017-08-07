TRISB = 0xff;  // Configure PORTB as Input.
 
TRISC = 0x00; // Configure PORTC as Output.
 
TRISD = 0x0F; // Configure lower nibble of PORTD as Input and higher nibble as Output
 
TRISD = (1<<0) | (1<<3) | (1<<6); // Configure PD0,PD3,PD6 as Input and others as Output
                                  // 
                                  // PORTB = 0xff;  // Make all PORTB pins HIGH.
 
PORTC = 0x00;  // Make all PORTC pins LOW..
 
PORTD = 0x0F;  // Make lower nibble of PORTD as HIGH and higher nibble as LOW 
 
PORTD = (1<<PD0) | (1<<PD3) | (1<<PD6); // Make PD0,PD3,PD6 HIGH,
 
