/*
 * XBee_rx.c
 *
 * Created: 2020-02-07 오후 1:18:46
 * Author : sukhyun3523
 */ 
// Xbee_rx

#define	F_CPU	16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "UART1.h"
#include "UART0.h"

FILE OUTPUT = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT	= FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

ISR(USART0_RX_vect)
{
	uint8_t oldSREG = SREG;			// 상태 레지스터 값 저장
	
	cli();							// 인터럽트 
	
	printf("%c", UDR0);
	
	SREG = oldSREG;					// 이전 상태 레지스터 값 복원
}

int main(void)
{
	stdout = &OUTPUT;					// printf 사용 설정
	stdin = &INPUT;						// scanf 사용 설정
	
	UART1_init();						// UART1 초기화
	UART0_init();						// UART0 초기화
	
	UCSR0B |= (1 << RXCIE0);			// 송신 가능 대기
	sei();								// 전역적으로 인터럽트 허용
	
	
	while (1)
	{
										// 반복 실행 부분
	}
	
	return 0;
}