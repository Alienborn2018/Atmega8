/*
 * ctrl.h
 *
 *  Procedures for handling Encoder SWITCH and GREEN LED
 *  GREEN LED 		- Is used to blink each time event is detected (e.g. switch pressed, volume changed, etc...)
 *
 *  Ports:
 *  SWITCH_1 PC0 	- Defines PC0 as ENCODER switch input
 *  LED_GREEN PC1	- Defines PC1 as GREEN LED output
 *
 *  Timers:
 *  TIMER1 			- Used as counter to blink GREEN LED each times it overflows
 *
 *  Constants:
 *  T1_PRESET 		- TIMER1 pre-set value
 *  T1_COUNT 		- Number of blinks per each event detected
 *
 *  Macros:
 *  SET_GREEN_LED_PIN	- Set GREEN_LED as output
 *  GREEN_LED_ON		- Switch On Led
 *  GREEN_LED_OFF		- Switch Off Led
 *  GREEN_LED_TOGGLE	- Toggle Led state
 *  SET_SWITCH_PIN		- Switch on pull-up resistor for Encoder SWITCH
 *  GET_SWITCH_STATE	- Reads current status of SWITCH
 */

#ifndef LED_GREEN_H_
#define LED_GREEN_H_

#endif /* LED_GREEN_H_ */

#define SWITCH_1 PC0
#define LED_GREEN PC1

#define T1_PRESET 65000
#define T1_COUNT 5

#define SET_GREEN_LED_PIN DDRC |= 1U << LED_GREEN
#define GREEN_LED_ON PORTC |= 1U << LED_GREEN
#define GREEN_LED_OFF PORTC &= ~(1U << LED_GREEN)
#define GREEN_LED_TOGGLE PORTC ^= 1U << LED_GREEN

#define SET_SWITCH_PIN PORTC |= 1U << SWITCH_1
#define GET_SWITCH_STATE (PINC & (1U << SWITCH_1))

volatile char timer1_overflow_count;
volatile char switch_1_old;

void ctrl_init (void);
void ctrl_timer_1_start(void);
void ctrl_timer_1_stop(void);

void ctrl_green_led_off(void);
void ctrl_green_led_on(void);
void ctrl_green_led_toggle(void);

signed char is_switch_1_changed(void);

void ctrl_green_led_tick(void);
void ctrl_run(void);
