/*
* main.c
*
* This project involves using the STK600 to control the operation of the rMP3 play back
* module from Rogue robotics and display track title and control information on a 2 row
* by 24 character LCD.
*
* PORTB for LCD data:
*
* B.0 LCD D0 U301 PIN 22
* B.1 LCD D1 U301 PIN 23
* etc. etc.
* B.7 LCD D7 U301 PIN 29
*
* PORTA for LCD control:
*
* A.7 LCD RS U301 PIN 16
* A.6 LCD E U301 PIN 17

* A.5 LCD R/!W U301 PIN 18
* Created: 4/17/2015 7:38:27 AM
* Author: Drew Radcliff
*/

#include "main" //include main.h file
//start of main function

int main(void)
{
	uint16_t song = 0;
	uint8_t start = 1;
	uint8_t pause = 0;
	
	char instructions[] = {&quot;B0 PP,B1 stp,B2-&gt;,B3&lt;-&quot;}; //user instructions
	
	//displays for button presses
	char msg1[] = {&quot;Play&quot;};
	char msg2[] = {&quot;Stop&quot;};
	char msg3[] = {&quot;Next&quot;};
	char msg4[] = {&quot;Previous&quot;};
	char msg5[] = {&quot;Pause&quot;};
	char msg6[] = {&quot;**STOPPED**&quot;}; //visible when stopped
	char msg7[] = {&quot;**PAUSED**&quot;}; //visible when paused
	
	//MP3 module commands
	char PlayPause[] = {&quot;PC P\r&quot;}; //play/pause command
	char Stop[] = {&quot;PC S\r&quot;}; //stop command
	char SongCommand[] = {&quot;PC F /&quot;}; //start song command
	//char Titles[10][25] = {&quot;05 Stay.mp3&quot;, &quot;02 Men in Black.mp3&quot;, &quot;00 Beat It.mp3&quot;,
	//&quot;06 Bad.mp3&quot;, &quot;08 Man in the Mirror.mp3&quot;, &quot;17 Funkytown.mp3&quot;, &quot;14 Wild Wild West.mp3&quot;,
	//&quot;09 Thriller.mp3&quot;, &quot;03 Dancing Queen.mp3&quot;, &quot;05 I Will Survive.mp3&quot;};
	char endCommand[] = {&quot;\r&quot;}; //end of start song
	
	init_ports(); //initialize ports
	init_LCD(); //initialize LCD
	init_UART(); //initialize UART
	sei(); //initialize interrupt
	
	LCD_write(INSTR_WR, 0x01); //clear LCD
	_delay_ms(2);
	LCD_write(INSTR_WR, 0x02);
	_delay_ms(2);
	
	UART_Tx_string(PlayPause); //send play command to MP3
	LCD_write(INSTR_WR, 0xC0); //write instructions on bottom line of LCD
	_delay_us(50);
	print_string(instructions);

	while(1)
	{
		if((PINC &amp; 0x01) == 0) //Play / Pause
		{
			LCD_write(INSTR_WR, 0x01); //clear LCD
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x02);
			_delay_ms(2);
			Parse_string(Titles[song], ParsedTitle); //parse song title
			print_string(ParsedTitle);

			//display parsed title

			LCD_write(INSTR_WR, 0xC0); // Set DDRAM address to bottom row, left character

			_delay_us(50);
			//start
			if(start)
			//checks if start is logic 1
			{
				//sends start song command to MP3
				UART_Tx_string(SongCommand);
				UART_Tx_string(Titles[song]);
				UART_Tx_string(endCommand);
				print_string(msg1);

				//display play message
				start = 0;

				//set start to zero

				_delay_ms(750);
				pause = 1;

				//set pause to 1

				LCD_write(INSTR_WR, 0x01); //clear LCD screen

				_delay_ms(2);
				LCD_write(INSTR_WR, 0x02);
				_delay_ms(2);
				Parse_string(Titles[song], ParsedTitle); //parse song title
				print_string(ParsedTitle);

				//display parsed title
			}
			//pause
			else if(pause)
			//checks if pause is logic 1
			{
				UART_Tx_string(PlayPause); //send pause

				command to MP3

				print_string(msg5);

				//display pause message on LCD
				_delay_ms(750);
				LCD_write(INSTR_WR, 0x01); //clear LCD
				_delay_ms(2);
				LCD_write(INSTR_WR, 0x02);
				_delay_ms(2);
				print_string(msg7);
				//display paused message until unpaused

				pause = 0;
				//set pause to 0
			}
			//play
			else
			{
				UART_Tx_string(PlayPause); //send play

				command to MP3

				print_string(msg1);

				//display play message on LCD
				_delay_ms(750);
				pause = 1;

				//set pause to 1

				LCD_write(INSTR_WR, 0x01); //clear LCD
				_delay_ms(2);
				LCD_write(INSTR_WR, 0x02);
				_delay_ms(2);
				Parse_string(Titles[song], ParsedTitle); //parse song title
				print_string(ParsedTitle); //display parsed song title
			}
			//display instructions on bottom line of LCD
			LCD_write(INSTR_WR, 0xC0);
			_delay_us(50);
			print_string(instructions);
		}
		//stop
		if((PINC &amp; 0x02) == 0) //checks if stop button is pressed
		{
			LCD_write(INSTR_WR, 0x01); //clear LCD
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x02);
			_delay_ms(2);
			Parse_string(Titles[song], ParsedTitle); //parse song title
			print_string(ParsedTitle); //display parsed title
			LCD_write(INSTR_WR, 0xC0); // Set DDRAM address to bottom row, left character

			_delay_us(50);
			print_string (msg2); //display stop message
			_delay_ms(750);
			LCD_write(INSTR_WR, 0x01); //clear LCD
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x02);
			_delay_ms(2);	
			print_string(msg6); //display stopped message

			//display instructions on bottom line of LCD
			LCD_write(INSTR_WR, 0xC0);
			_delay_us(50);
			print_string(instructions);
			UART_Tx_string(Stop);
			start = 1;
		}
		//next
		if((PINC &amp; 0x04) == 0) //checks for next buttom press
		{
			LCD_write(INSTR_WR, 0x01); //clear LCD
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x02);
			_delay_ms(2);
			Parse_string(Titles[song], ParsedTitle); //parse song title
			print_string(ParsedTitle); //display parsed title
			LCD_write(INSTR_WR, 0xC0); // Set DDRAM address to bottom row, left character

			_delay_us(50);
			print_string (msg3); //display next message
			_delay_ms(750);
			song++;
			//increment song

			UART_Tx_string(SongCommand); //start song command sent to MP3

			UART_Tx_string(Titles[song]);
			UART_Tx_string(endCommand);
			LCD_write(INSTR_WR, 0x01); //clear LCD
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x02);
			_delay_ms(2);
			Parse_string(Titles[song], ParsedTitle); //parse song title
			print_string(ParsedTitle); //display parsed title
			LCD_write(INSTR_WR, 0xC0); //display instructions to bottom line of LCD

			_delay_us(50);
			print_string(instructions);
		}
		//previous
		if((PINC &amp; 0x08) == 0) //checks if previous push button is pressed
		{
			LCD_write(INSTR_WR, 0x01); //clear LCD
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x02);
			_delay_ms(2);
			Parse_string(Titles[song], ParsedTitle); //parse song title
			print_string(ParsedTitle); //display parsed title
			LCD_write(INSTR_WR, 0xC0); // Set DDRAM address to bottom row, left character
			_delay_us(50);
			print_string (msg4); //display previous message to LCD

			_delay_ms(750);
			if(song&gt;0) //will not decrement song if it is the first song in the array
			{
				//decrement song and send start song command to MP3
				song--;

				UART_Tx_string(SongCommand);
				UART_Tx_string(Titles[song]);
				UART_Tx_string(endCommand);
			}
			LCD_write(INSTR_WR, 0x01); //clear LCD
			_delay_ms(2);
			LCD_write(INSTR_WR, 0x02);
			_delay_ms(2);
			Parse_string(Titles[song], ParsedTitle); //parse song title
			print_string(ParsedTitle); //display parsed title
			LCD_write(INSTR_WR, 0xC0); //write instructions to bottom line of LCD

			_delay_us(50);
			print_string(instructions);
		}
		//This function is used to read from the EEPROM and add the song titles to the Titles array

		if((PINC &amp; 0x40) == 0) //checks if EEPROM read button is pressed
		{
			uint16_t address = 0; //initialize address

			variable to 0

			for(uint8_t k=0; k&lt;10; k++) //loop for 10 songs
			{
				for(uint8_t j=0; j&lt;25; j++) //loop for the amount of characters in each song
				{
					if(Titles[k][j] != &#39;\0&#39;) //check if character is a null character
					{
						Titles[k][j] = EEPROM_read(address); //read EEPROM character from address variable to Titles array

						address++; //increment address

					}
					//end of song
					else
					{
						Titles[k][j] = EEPROM_read(address); //read EEPROM character from address variable to Titles array

						address++; //increment address one more time

						break; //break from loop

					}
				}
			}
		}
	}
} //end of main
