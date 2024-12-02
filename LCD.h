/*
 * LCD.h
 *
 *	Provides LCD functions such as initialization, sending
 *	commands and data, and basic functionalities
 *
 * Created on: July 26th, 2023
 *		Author: Jackie Huynh
 *
 */
 
#ifndef LCD_H_
#define LCD_H_
#include "util.h"

/*************PCF8574A Register*************/
#define LCD_WRITE_ADDR			(0x3FU)
#define PCF8574A_REG				(0x00U)

/**************LCD CMD Register*************/
#define INIT_REG_CMD				(0x30U)
#define INIT_FUNC_CMD				(0x20U)

#define FUNC_MODE						(0x20U)
	#define FUNC_4_BIT				(0x00U)
	#define FUNC_2_ROW				(0x08U)
	#define FUNC_5_7					(0x00U)
	
#define DISP_CMD						(0x08U)
	#define DISP_ON						(0x04U)
	#define DISP_OFF					(0x00U)
	#define DISP_CURSOR_ON		(0x02U)
	#define DISP_CURSOR_OFF		(0x00U)
	#define DISP_BLINK_ON			(0x01U)
	#define DISP_BLINK_OFF		(0x00U)
	
#define CLEAR_DISP_CMD			(0x01U)

#define ENTRY_MODE_CMD			(0x04U)
	#define ENTRY_INC_CURSOR	(0x02U)
  #define ENTRY_DISP_SHIFT	(0x01U)
	
#define RETURN_HOME_CMD			(0x02U)

#define FIRST_ROW_CMD				(0x80U)
#define SECOND_ROW_CMD			(0xC0U)

/* LCD Module Macros */
#define RS_Pin							(0x01U)
#define RW_Pin							(0x02U)
#define EN_Pin							(0x04U)
#define BACKLIGHT						(0x08U)

/* General Macros */
#define UPPER_NIBBLE_MSK		(0xF0U)
#define NIBBLE_SHIFT				(0x4U)
#define ROW1								(0U)
#define ROW2								(1U)
#define LCD_ROW_SIZE				(16)

#include <stdint.h>

/*
 *	-------------------LCD_Init------------------
 *	Basic LCD Initialization Function
 *	Input: None
 *	Output: None
 */
void LCD_Init(void);

/*
 *	-------------------LCD_Clear------------------
 *	Clear the LCD Display by passing a command
 *	Input: None
 *	Output: None
 */
void LCD_Clear(void);

/*
 *	----------------LCD_Set_Cursor----------------
 *	Set Cursor to Desire Place
 *	Input: Desired Row and Column to place Cursor
 *	Output: None
 */
void LCD_Set_Cursor(uint8_t row, uint8_t col);

/*
 *	---------------LCD_Reset_Cursor---------------
 *	Reset Cursor back to Row 1 and Column 0
 *	Input: None
 *	Output: None
 */
void LCD_Reset_Cursor(void);

/*
 *	----------------LCD_Print_Char----------------
 *	Prints a Character to LCD
 *	Input: Character Hex Value
 *	Output: None
 */
void LCD_Print_Char(uint8_t data);

/*
 *	----------------LCD_Print_Str-----------------
 *	Prints a string to LCD
 *	Input: Pointer to Character Array
 *	Output: None
 */
void LCD_Print_Str(uint8_t* str);

#endif