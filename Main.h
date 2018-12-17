/*
* main.h
*
* This files contains all the defines, includes, and global variables needed for the
program
*
* Created: 4/30/2015 1:41:47 PM
* Author: Drew Radcliff
*/

#ifndef MAIN_H_ //include macro guard
#define MAIN_H_ //ensure independence

//includes
#include &lt;avr/io.h&gt;
#include &lt;avr/interrupt.h&gt;
#include &lt;util/delay.h&gt;
#include &quot;ports.h&quot;
#include &quot;UART.h&quot;
#include &quot;LCD.h&quot;

//global variables
volatile uint16_t rx_array[25];
volatile uint16_t i;
volatile uint16_t new_press;
volatile char ParsedTitle[30];
volatile char mem[30];
volatile char Titles[10][25];

#endif /* MAIN_H_ */
