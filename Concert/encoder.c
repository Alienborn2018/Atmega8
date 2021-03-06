
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "encoder.h"
#include "ctrl.h"
#include "lcd_1602.h"
#include "volume_bar.h"
#include "serial.h"

//INT0 interrupt
ISR (INT0_vect) { //ENC_A

	if(!bit_is_clear(ENC_PIN, ENC_B)) {
		encoder_turn_up();
	} else {
		encoder_turn_down();
	}
}

//INT1 interrupt
ISR (INT1_vect) { //ENC_B

	if(!bit_is_clear(ENC_PIN, ENC_A)) {
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
	DDRD &= ~(1U << ENC_A); // Set PD2 as input
	DDRD &= ~(1U << ENC_B); // Set PD3 as input
	PORTD |= (1U << ENC_A) | (1U << ENC_B); // Switch on pull-up resistors

	MCUCR |= (1U << ISC01); // INT0 - falling edge
	MCUCR &= (1U << ISC00);
	MCUCR |= (1U << ISC11) | (1U << ISC10); // INT1 - raising edge

	GICR |= (1U << INT0) | (1U << INT1); // Enable INT0 and INT1

	TIMSK |= 1U << TOIE0; // Enable timer 0 overflow interrupt
	TCNT0 = T0_PRESET;

	encoder_timer_0_start();

	vol_current = 0;
	vol_old = vol_current + 1; // to force update after re-start
}

void encoder_turn_up(void) {
	if (vol_current < VOL_MAX) {
		vol_current += 1;

	}
	serial_send_byte('+');
	//ctrl_green_led_tick();
}

void encoder_turn_down(void) {
	if (vol_current > VOL_MIN ) {
		vol_current -= 1;

	}
	serial_send_byte('-');
	//ctrl_green_led_tick();
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
	char str[32];

	if (vol_current != vol_old)	{
		if(vol_current > VOL_MAX)
			vol_current = VOL_MAX;

		sprintf(str, "%04d", (int) vol_current);
		lcd_printfxy(1, 12, str);

		vol_old = vol_current;
	}

}

