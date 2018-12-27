/*
 * serial.c
 *
 *  Created on: 22 gru 2018
 *      Author: Lucyna
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "serial.h"
#include "ctrl.h"
#include "lcd_1602.h"

ISR(USART_RXC_vect) {

   ser_val = UDR;
   if(ser_buf_index<32)
	   ser_buf_index += 1;
   ser_buf[ser_buf_index] = (unsigned char) ser_val;
}

void serial_init(void) {

	UBRRL = BAUD_PRESCALE; // Load lower 8-bits into the low byte of the UBRR register
	UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits into the high byte of the UBRR register

	ser_val = 0;
	ser_val_old = ser_val;
	ser_buf_index = -1;

	UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE)); // Enable receiver and transmitter and receive complete interrupt
}

void serial_send_byte(uint8_t u8Data) {

  while((UCSRA &(1<<UDRE)) == 0); // Wait until last byte has been transmitted
  UDR = u8Data; // Transmit data
}

uint8_t serial_receive_byte(void){
  while((UCSRA &(1<<RXC)) == 0); // Wait until last byte has been received
  return UDR;
}

void serial_run(void) {
	char str[32];

	if(ser_val != ser_val_old) {
		ser_val_old = ser_val;
		ctrl_green_led_tick();

		sprintf(str, "%c", ser_val);
		lcd_printfxy(0, 9, str);
	 }
}
