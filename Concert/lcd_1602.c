/*
 * lcd_1602.c
 *
 *  Procedures for LCD 1602A display 2 Lines x 16 Characters
 *  Created on: Dec 16, 2018
 *  Author: Piotr Ostrowski
 *
 *  Procedures:
 *  lcd_init		- Initializes display (Swich On, Sert 4Bit Mode, Hides cursor, Cleares)
 *  lcd_cmd			- Write atomic command
 *  lcd_put			- Write single char
 *  lcd_gotoxy		- set cursor at x,y position; x: 0-1; y: 0-15
 *  lcd_printf		- Write string from current cursor position
 *  lcd_printfxy	- Write string from x,y position
 *  lcd_wellcome 	- Display welcome text /w Build timestamp
 */

#include <avr/io.h>
#include <util/delay.h>

#include "lcd_1602.h"
#include "lcd_1602_custom_char.h"

void lcd_init(void) {
	SET_LCD_PORT;
	SET_LCD_RS_EN;
	_delay_ms(40); //LCD Power ON delay always >15ms

	lcd_cmd(0x33);
	lcd_cmd(LCD_4BIT);
	lcd_cmd(LCD_2LINE5x7);
	lcd_cmd(LCD_ON);
	lcd_cmd(LCD_CLEAR);
	_delay_ms(250);
	lcd_wellcome();
	_delay_ms(1500);
	lcd_cmd(LCD_CLEAR);
}

void lcd_cmd(char c) {
	LCD_NIBBLE_HIGH;
	LCD_RS_LOW;
	LCD_EN_HIGH;
	_delay_us(LAT_1);
	LCD_EN_LOW;
	_delay_us(LAT_2);

	LCD_NIBBLE_LOW;
	LCD_RS_LOW;
	LCD_EN_HIGH;
	_delay_us(LAT_1);
	LCD_EN_LOW;
	_delay_us(LAT_2);
	if((c == LCD_CLEAR) | (c == LCD_HOME)) {
		_delay_ms(LAT_3);
	}
}

void lcd_put(char c) {
	LCD_NIBBLE_HIGH;
	LCD_RS_HIGH;
	LCD_EN_HIGH;
	_delay_us(LAT_1);
	LCD_EN_LOW;
	_delay_us(LAT_1);

	LCD_NIBBLE_LOW;
	LCD_RS_HIGH;
	LCD_EN_HIGH;
	_delay_us(LAT_1);
	LCD_EN_LOW;
	_delay_us(LAT_1);
}

void lcd_gotoxy(char x, char y) {
	int addr = 0x00;
	unsigned char pos;

	if (x == 1)
		addr = 0x40;
	pos = (unsigned char) (addr + y);
	lcd_cmd(0x80 | pos);
}

void lcd_printf(char* c) {
	int i;

	for(i=0; c[i] != 0; i++) {
		lcd_put(c[i]);
	}
}

void lcd_printfxy(char x, char y, char* c) {
	int i;

	lcd_gotoxy (x, y);
	for(i=0; c[i] != 0; i++) {
		lcd_put(c[i]);
	}
}


void lcd_wellcome(void) {
	lcd_printfxy(0, 0, "Build:");
	lcd_printfxy(1 ,0, __DATE__);
}
