/*
 * Xbee_tx.c
 *
 * Created: 2020-02-06 오후 2:18:06
 * Author : sukhyun3523
 */ 

// Xbee tx
#define	F_CPU	16000000L
#include <avr/io.h>
#include <stdio.h>
#include "UART1.h"
#include "UART0.h"

FILE OUTPUT \
 = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);

FILE INPUT	\
 = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

int main(void)
{
	stdout = &OUTPUT;							// printf 사용 설정
	stdin = &INPUT;								// scanf 사용 설정
	
	UART1_init();								// UART1 초기화
	UART0_init();
	
	while (1)
	{
		uint8_t data_in;
		scanf("%c", &data_in);
		UART0_transmit(data_in);
		printf("%c", data_in);
		
	}

	return 0;

}