/*
 * UART1.h
 *
 * Created: 2020-01-03 오후 8:53:50
 *  Author: gpwns
 */ 


#define UART1_H_

void UART1_init(void);
void UART1_transmit(char data);
unsigned UART1_receive(void);
void UART1_print_string(char *str);
void UART1_print_1_byte_number(uint8_t n);
void UART1_print_float(float f);
