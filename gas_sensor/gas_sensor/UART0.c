/*
 * UART0.c
 *
 * Created: 2020-01-06 오후 1:05:31
 *  Author: gpwns
 */ 

#include <avr/io.h>
#include <stdio.h>

void UART0_init(void)
{
	
	UBRR0H = 0x00;
	UBRR0L = 207;
	
	UCSR0A |= _BV(U2X0);
	UCSR0C |= 0x06;
	
	UCSR0B |= _BV(RXEN0);
	UCSR0B |= _BV(TXEN0);
}

void UART0_transmit(char data)
{
	
	while( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = data;
}

unsigned char UART0_receive(void)
{
	while( !(UCSR0A & (1 << RXC0)) );
	return UDR0;
}

void UART0_print_string(char *str)
{
	for(int i = 0; str[i]; i++)
	UART0_transmit(str[i]);
}

void UART0_print_1_byte_number(uint8_t n)
{
	char numString[4] = "0";
	
	sprintf(numString, "%d", n);
	UART0_print_string(numString);
}

void UART0_print_float(float f)
{
	char numString[20] = "0";
	
	sprintf(numString, "%f", f);
	UART0_print_string(numString);
}