/*
* LCD.c
*
* This file is used to create all functions used with the LCD
* including: initializing, check busy, LCD write, print string, and parse string
*
* Created: 4/30/2015 2:00:00 PM
* Author: Drew Radcliff
*/

#include "main.h"

//function to initialize the LCD
void init_LCD (void)
{
  _delay_ms(35); /* wait for more than 30mS after VDD rises to 4.5V */
  LCD_write(INSTR_WR,0x38); /* function set 8bits, 2line, display off */
  _delay_us(50); /* wait for more than 39microS */
  LCD_write(INSTR_WR,0x0C); /* display on, cursor off, blink off */
  _delay_us(50); /* wait for more than 39microS */
  LCD_write(INSTR_WR,0x01); /* display clear */
  _delay_ms(2); /* wait for more than 1.53mS */
  LCD_write(INSTR_WR,0x06); /* entry mode set, increment mode */
}
//function to check if the LCD is busy
void check_busy(void)
{
  PORTA = 0b00100000; //RW = 1, E = RS = 0
  DDRB = DDRB &amp; 0b01111111; //set B7 as ip
  do
  {
    PORTA = PORTA | 0b01000000; //enable high
    PORTA = PORTA &amp; 0b00100000; //enable low keep read
  } while (PINB &amp; 10000000);
  DDRB = 0b11111111; //PORTB all op
}

//function to write to the LCD
void LCD_write(unsigned char RS, unsigned char data)
{
  check_busy();
  
  if(RS == DATA_WR) //write data RS = 1 E = 0, RW = 0
    PORTA = 0b10000000; //write instruction
  else
    PORTA = 0b00000000;
  
  PORTA = PORTA | 0x40; //set E high
  PORTB = data;
  _delay_ms(50);
  PORTA = PORTA &amp; 0x80; //reset E low
  _delay_ms(50);
}

//function to print character string to the LCD
void print_string(char *str_ptr)
{
  while(*str_ptr != &#39;\0&#39;) //loops until null character
  {
    check_busy();
    PORTA = 0b10000000; //write data to LCD
    PORTA = PORTA | 0x40;
    PORTB = *str_ptr; //get data and put in PORTB
    str_ptr++; //increment data to next character in string

    PORTA = PORTA&amp;0x80;
  }
}

//function to remove unwanted parts of the song title string
void Parse_string(char *MP3_ptr, char *Title_ptr)
{
  for(uint8_t x=0; x&lt;30; x++)
  {
    ParsedTitle[x] = &#39; &#39;; //clears parsed title array
  }
  MP3_ptr++; //skip the first character address
  
  //increment pointer until second space encountered to skip the file size info
  do
  {
    MP3_ptr++;
  } while (*MP3_ptr != &#39; &#39;);
  MP3_ptr++; //skip over the second space address

  //copy all characters up to but excluding the . in .mp3
  do
  {
    *Title_ptr = *MP3_ptr;
    Title_ptr++;
    MP3_ptr++;
  } while (*MP3_ptr != &#39;.&#39;); //stop copying when the . in .mp3 is reached
}
