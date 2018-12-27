/*
 * run.c
 *
 *  Main loop
 *  Created on: Dec 16, 2018
 *  Author: Piotr Ostrowski
 *
 *  Procedures:
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#include "run.h"
#include "lcd_1602.h"
#include "lcd_1602_custom_char.h"
#include "ctrl.h"
#include "settings.h"
#include "encoder.h"
#include "volume_bar.h"
#include "serial.h"

int main (void) {
	lcd_init();
	ctrl_init();
	encoder_init();
	vol_bar_init();
	serial_init();

    sei(); // Enable interrupts
   	while (1) {
   		ctrl_run();
   		encoder_run();
   		vol_bar_run();
   		serial_run();
		_delay_ms(10);
   	}
   	return (0);
}

