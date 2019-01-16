/*
 * lcd_1602.h
 *
 *  Procedures for LCD 1602A display 2 Lines x 16 Characters
 *  Created on: Dec 16, 2018
 *  Author: Piotr Ostrowski
 *
 *  Ports:
 *  PD4-7 			- Define PD4-7 as 4-bit data bus for LCD
 *  RS PC3 			- Define PC3 as RS
 *  EN PC2 			- Define PC2 as EN
 *
 *  Constants:
 *  LAT_1 50 		- Defines delay in microseconds for data validity for data write
 *  LAT_2 200 		- Defines delay in microseconds after data write
 *  LAT_3 2 		- Defines delay in milliseconds for LCD clear command
 *
 *  Macros:
 *  SET_LCD_PORT	- Set LCD Port (PD4-7) as output
 *  LCD_RS_HIGH 	- Set RS High
 *  LCD_RS_LOW		- Set RS Low
 *  LCD_EN_HIGH		- Set EN High
 *  LCD_EN_LOW 		- Set EN Low
 *  LCD_NIBBLE_HIGH - Set High Nibble for 4 bit communication
 *  LCD_NIBBLE_LOW	- Set Low Nibble for 4 bit communication
 *
 *  LCD Commands:
 *  LCD_CLEAR		- Clears LCD Display
 *  LCD_HOME		- Moves cursor to start
 *  LCD_4BIT		- Sets up LCD in 4bit mode
 *  LCD_2LINE5x7	- Sets 2 line, 5*7 matrix in 4-bit mode
 *  LCD_ON			- Display On cursor Off
 *
 */

#ifndef LCD_1602_H_
#define LCD_1602_H_

#define LAT_1 100
#define LAT_2 200
#define LAT_3 2

#define RS PC3
#define EN PC2

#define SET_LCD_PORT DDRD |= 0xF0
#define SET_LCD_RS_EN DDRC |= (1U << RS ) | (1U << EN)
#define LCD_RS_HIGH PORTC |= 1U << RS
#define LCD_RS_LOW PORTC &= ~(1U << RS)
#define LCD_EN_HIGH PORTC |= 1U << EN
#define LCD_EN_LOW PORTC &= ~(1U << EN)

#define LCD_NIBBLE_HIGH PORTD = c & 0xF0
#define LCD_NIBBLE_LOW PORTD = ((c << 4) & 0xF0)

#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_4BIT 0x32
#define LCD_2LINE5x7 0x28
#define LCD_ON 0x0c

void lcd_init(void);
void lcd_cmd(char c);
void lcd_put(char c);
void lcd_gotoxy(char x, char y);
void lcd_printf(char* c);
void lcd_printfxy(char x, char y, char* c);
void lcd_wellcome(void);

#endif /* LCD_1602_H_ */
