/*
* ports.c
*
* this file holds the port initialization function assigning the inputs and outputs
*
* Created: 4/30/2015 1:45:41 PM
* Author: Drew Radcliff
*/

#include "main.h" //include main.h file

//initializes ports on the STK board
void init_ports(void)
{
  DDRC = 0x00; //PORTC set to switches
  PORTC = 0xFF;
  DDRB = 0xFF; //PORTB set to output to LCD
  PORTB = 0x00;
  DDRA = 0xE0; //output to LCD controls
  DDRD = 0xFF;
  PORTD = 0x00; //PORTD to LCD
}
