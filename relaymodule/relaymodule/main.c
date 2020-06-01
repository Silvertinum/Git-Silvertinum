/*
 * relaymodule.c
 *
 * Created: 2020-04-21 오후 5:33:07
 * Author : SAMSUNG
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "UART1.h"

FILE OUTPUT \
 = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT \
 = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);
 
int main(void)
{
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART1_init();
	
	DDRA |= 0x01;
	DDRB |= 0x01;
	DDRC |= 0x01;
	DDRD |= 0x01;

	char data;
	
    while (1) 
    {
		scanf("%c", &data);
		
		printf("channel \n", data);
		
		if(data == '1'){
			PORTA |= 0x01;
			PORTB &= 0xFE;
			PORTC &= 0xFE;
			PORTD &= 0xFE;
			
			printf("channel No.1! \r\n");
		}
		
		else if(data == '2'){
			PORTA &= 0xFE;
			PORTB |= 0x01;
			PORTC &= 0xFE;
			PORTD &= 0xFE;
			
			printf("channel No.2! \r\n");
			}
			
		else if(data == '3'){
			PORTA &= 0xFE;
			PORTB &= 0xFE;
			PORTC |= 0x01;
			PORTD &= 0xFE;
			
			printf("channel No.3! \r\n");
			}
			
		else{
			PORTA &= 0xFE;
			PORTB &= 0xFE;
			PORTC &= 0xFE;
			PORTD |= 0x01;1
			
			printf("channel No.4! \r\n");
		}
	}

	return 0;
}

