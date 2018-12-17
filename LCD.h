/*
* LCD.h
*
* This file includes all the defines and prototypes needed for the LCD
*
* Created: 4/30/2015 1:54:53 PM
* Author: Drew Radcliff
*/

#ifndef LCD_H_ //include macro guard
#define LCD_H_ //ensure independence

//defines
#define INSTR_WR 0 //instruction write set to 0
#define DATA_WR 1 //data write set to 1

//external global variables
extern volatile char ParsedTitle[30]; //external global variable parsed title array

#endif /* LCD_H_ */
