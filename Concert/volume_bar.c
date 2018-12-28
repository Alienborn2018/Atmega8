#include <stdio.h>

#include "volume_bar.h"
#include "ctrl.h"
#include "lcd_1602.h"
#include "lcd_1602_custom_char.h"

void vol_bar_init(void) {

	bar_current = 0;
	bar_old = bar_current + 1; // to force update after re-start
	vol_current = 0;
	vol_old = vol_current + 1; // to force update after re-start
}

void bar_update(unsigned int vol) {
	lcd_gotoxy(1,0);
	for(unsigned int i=0; i<=vol; i++)
		lcd_put(i);
	if (vol < BAR_MAX)
		for(unsigned int i=(vol+1); i<=BAR_MAX; i++)
			lcd_put(0);
}

void vol_bar_run(void) {
	char str[32];
	unsigned int vol_bar_rat;

	lcd_load_custom_characters(0);
	lcd_gotoxy(0,0);
	lcd_printf("Volume:");

	/*
	if (vol_current != vol_old)	{
		if(vol_current > VOL_MAX)
			vol_current = VOL_MAX;

		sprintf(str, "%04d", (int) vol_current);
		lcd_printfxy(1, 12, str);

		vol_bar_rat = (unsigned int) VOL_MAX / (unsigned int) BAR_MAX;
		bar_current = vol_current / vol_bar_rat;
		vol_old = vol_current;
	}
	if (bar_current != bar_old)	{
		if (bar_current > BAR_MAX)
			bar_current = BAR_MAX;

		sprintf(str, "%01d", (int) bar_current);
		lcd_printfxy(1, 9, str);

		bar_update(bar_current);
		bar_old = bar_current;
	}*/
}
