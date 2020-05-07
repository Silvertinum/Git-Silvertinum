/*
 * UART0.h
 *
 * Created: 2020-01-06 오후 1:05:50
 *  Author: gpwns
 */ 


#ifndef UART0_H_
#define UART0_H_

void UART0_init(void);
void UART0_transmit(char data);
unsigned UART0_receive(void);
void UART0_print_string(char *str);
void UART0_print_1_byte_number(uint8_t n);
void UART0_print_float(float f);


#endif /* UART0_H_ */