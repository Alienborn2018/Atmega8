/*
 * volume_bar.h
 *
 *  vol_curent - updated from module encoder.h
 *
 *  Created on: 19 gru 2018
 *  Author: Piotr Ostrowski
 */

#ifndef VOLUME_BAR_H_
#define VOLUME_BAR_H_

#endif /* VOLUME_BAR_H_ */

#define VOL_MIN 0
#define VOL_MAX 300
#define BAR_MIN 0
#define BAR_MAX 7

volatile unsigned int vol_old;
volatile unsigned int vol_current; // Actual volume value in range (VOL_MIN, VOL_MAX)
volatile unsigned int bar_old;
volatile unsigned int bar_current; // Actual bar value in range (BAR_MIN, BAR_MAX)

void vol_bar_init(void);
void bar_update(unsigned int vol); // Translates actual volume value to bar value
void vol_bar_run(void);
