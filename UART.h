/*
* UART.h
*
* This file includes all of the defines, prototypes, and varaibles used for UART
*
* Created: 4/30/2015 1:48:50 PM
* Author: Drew Radcliff
*/

#ifndef UART_H_ //include macro guard
#define UART_H_ //ensure independence

//defines
#define F_CPU 8000000UL
#define BAUD 9600

//external prototypes
extern void init_UART(void);
extern void UART_out(uint8_t ch);
extern void UART_Tx_string(char *string);

//external global variables
extern volatile uint16_t new_press;
extern volatile uint16_t i;
extern volatile uint8_t rx_char;

#endif /* UART_H_ */
