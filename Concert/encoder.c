
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "encoder.h"
#include "ctrl.h"
#include "lcd_1602.h"
#include "volume_bar.h"

//INT0 interrupt
ISR(INT0_vect ) {
	if(!bit_is_clear(PIND, PD3)) {
		encoder_turn_up();
	} else {
		encoder_turn_down();
	}
}

//INT1 interrupt
ISR(INT1_vect ) {
	if(!bit_is_clear(PIND, PD2)) {
		encoder_turn_up();
	} else {
		encoder_turn_down();
	}
}

//TIMER0 interrupt
ISR (TIMER0_OVF_vect) {
	TCNT0 = T0_PRESET;
	if (timer0_overflow_count < T0_COUNT)
		timer0_overflow_count += 1;
}

void encoder_init(void) {
	DDRD &= ~(1U << PD2); // Set PD2 as input
	DDRD &= ~(1U << PD3); // Set PD3 as input
	PORTD |= (1U << PD2) | (1U << PD3); // Switch on pull-up resistors

	GICR |= (1U << INT0) | (1U << INT1); // Enable INT0 and INT1
	MCUCR |= (1 << ISC01) | (1 << ISC11) | (1 << ISC10); // INT0 - falling edge, INT1 - raising edge

	TIMSK |= 1U << TOIE0; // Enable timer 0 overflow interrupt
	TCNT0 = T0_PRESET;

	encoder_timer_0_start();
}

void encoder_turn_up(void) {
	if (vol_current < VOL_MAX) {
		vol_current += 1;
	}
}

void encoder_turn_down(void) {
	if (vol_current > VOL_MIN ) {
		vol_current -= 1;
	}
}

void encoder_timer_0_start(void) {
	timer0_overflow_count = 0;
	timer0_overflow_count_old = timer0_overflow_count;
	TCCR0 = (1U << CS02); //| 1U << (CS02); // Start timer 0 with / 1024 pre-scaler
}

void encoder_timer_0_stop(void) {
	TCCR0 &= ~(1U << CS02); //| 1U << (CS02)); // Stop timer 0
}

void encoder_run(void) {


}

