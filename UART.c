/*
* UART.c
*
* This file creates all the functions needed for the UART
* for initialization of the UAR, UART out, UART string transmit
* and interrupt functions
*
* Created: 4/30/2015 1:47:03 PM
* Author: Drew Radcliff
*/

#include "main.h" //include main.h file
volatile uint8_t rx_char; //create global variable for rx_char

//initializes the UART
init_UART(void)
{
  UCSR0A = 0b00000000;
  UCSR0B = 0b10011000; //enable Rx and Tx, no interrupt
  UCSR0C = 0b00000110; //asynch, no parity, 8 bit
  uint16_t myubr = (F_CPU/(16UL*BAUD)) - 1; //calculate myubr
  UBRR0L = myubr;
  UBRR0H = 0;
}

//sends a variable to the UART
void UART_out(uint8_t ch)
{
  while((UCSR0A &amp;(1 &lt;&lt; UDRE0)) == 0);
  {
    //wait for it to finish transmitting
  }
  UDR0 = ch;
}

//transmits a string from the UART
void UART_Tx_string(char *string)
{
  while(*string!=0) //loops until string pointer is 0
  {
    UART_out(*string); //sends pointer to UART
    string++; //increment pointer
  }
}

//interrupt used to read from the UART
ISR(USART0_RX_vect)
{
  char rx_char = UDR0; //read UDR0 to clear interrupt flag
  if(rx_char != 0x0D) //checks for character return
  {
    rx_array[i] = rx_char; //sets received character string to array
    i++; //increment index
  }
  else
  {
    i++; //increment index
    rx_array[i] = &#39;\0&#39;; //sets null character at the end of character string

    i = 0; //set index to 0
    new_press = 1; //new press set to 1 to notify that interrupt has occurred
  }
}
