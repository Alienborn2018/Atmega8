
/*
 * ctrl.c
 *
 *  Procedures for handling Encoder SWITCH and GREEN LED
 *  GREEN LED 		- Is used to blink each time event is detected (e.g. switch pressed, volume changed, etc...)
 *
 *  Procedures:
 *  ctrl_init 				- Initialize ports for GREEN LED and SWITCH
 *  ctrl_green_led_off		- Switch Off GREEN LED
 *  ctrl_green_led_on		- Switch On GREEN LED
 *  ctrl_green_led_toggle	- Toggle state of GREEN LED
 *  ctrl_timer_1_start		- Starts TIMER1 to start counting; Overflow Interrupt will be triggered
 *  ctrl_timer_1_stop		- Stops TIMER1
 *  is_switch_1_changed		- Verifies if SWITHC State changed
 *  ctrl_tick				- Triggers GREEN LED Blinking; GREEN LED will blink T_COUNT times and gets Off
 *  ctrl_run				- Loop to test status of SWITCH; Display status of SWITCH on screen; To be included in Main Loop (run.c)
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "ctrl.h"
#include "lcd_1602.h"
#include "lcd_1602_custom_char.h"
#include "encoder.h"
#include "volume_bar.h"
#include "serial.h"

// TIMER1 interrupt
ISR (TIMER1_OVF_vect) {
	TCNT1 = T1_PRESET;
	ctrl_green_led_toggle();

	timer1_overflow_count += 1;
	if (timer1_overflow_count >= T1_COUNT) {
		ctrl_green_led_off();
		ctrl_timer_1_stop();
	}
}

void ctrl_init (void) {
	SET_GREEN_LED_PIN;
	SET_SWITCH_PIN;
	TIMSK |= 1U << TOIE1; // Enable timer 1 overflow interrupt
	TCNT1 = T1_PRESET; // Set timer1 counter initial value to 0
    switch_1_old = !GET_SWITCH_STATE; // Preset current sate of Switch 1
}

void ctrl_green_led_off(void) {
	GREEN_LED_OFF;
}

void ctrl_green_led_on(void) {
	GREEN_LED_ON;
}

void ctrl_green_led_toggle(void) {
	GREEN_LED_TOGGLE;
}

void ctrl_timer_1_start(void) {
	timer1_overflow_count = 0;
	TCCR1B = (1U << CS12) | 1U << (CS12); // Start timer 1 with / 1024 pre-scaler
}

void ctrl_timer_1_stop(void) {
	TCCR1B &= ~((1U << CS12) | 1U << (CS12)); // Stop timer 1
}

signed char is_switch_1_changed(void) {
	if (switch_1_old != GET_SWITCH_STATE) {
		switch_1_old = GET_SWITCH_STATE;
		if (GET_SWITCH_STATE == (1U << SWITCH_1))
			return (1);
		else
			return (0);
	}
	return (-1);
}

void ctrl_green_led_tick(void) {
	ctrl_green_led_off();
	ctrl_timer_1_start();
}

void ctrl_run(void) {
	signed char flag1;

	flag1 = is_switch_1_changed();
	if ( flag1 >= 0 ) {
		ctrl_green_led_tick();
		if (flag1 == 1)	{
		 	lcd_printfxy(0, 13, " ON");
		} else {
			lcd_printfxy(0, 13, "OFF");
			timer0_overflow_count = 0;
			timer0_overflow_count_old = timer0_overflow_count;
		}
	}
}

