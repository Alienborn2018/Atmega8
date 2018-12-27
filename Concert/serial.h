/*
 *
 *  38400 Baud rate, 8 data bits, no parity, 1 stop bit
 *  USCB-COM Driver https://www.ftdichip.com/Drivers/VCP.htm
 *  Consle - Putty -> plink.exe -serial -sercfg ... < input.txt
 */



// Define baud rate
#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char ser_val;
volatile unsigned char ser_val_old;
volatile unsigned char ser_buf[32];
volatile unsigned char ser_cmd_buf[32];
volatile unsigned char ser_data_buf[32];
volatile unsigned char ser_buf_index;

void serial_init(void);
void serial_send_byte(uint8_t u8Data);
uint8_t serial_receive_byte(void);
void serial_run(void);
