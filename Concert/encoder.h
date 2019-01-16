/*
 * encoder.h
 *
 *  Created on: 17 gru 2018
 *      Author: Lucyna
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#endif /* ENCODER_H_ */

#define VOL_MIN 0
#define VOL_MAX 300

#define ENC_A PD2
#define ENC_B PD3
#define ENC_PIN PIND

#define T0_PRESET 0
#define T0_COUNT 300

volatile unsigned int vol_old;
volatile unsigned int vol_current; // Actual volume value in range (VOL_MIN, VOL_MAX)

volatile unsigned int timer0_overflow_count_old;
volatile unsigned int timer0_overflow_count;

void encoder_init(void);
void encoder_run(void);

void encoder_timer_0_start(void);
void encoder_timer_0_stop(void);

void encoder_turn_up(void);
void encoder_turn_down(void);

