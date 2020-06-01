/*
 * final_Capstone_bottom.c
 *
 * Created: 2020-05-06 오전 12:12:57
 * Author : SAMSUNG
 */ 

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

void ADC_init(unsigned char channel)
{
	ADMUX = (1 << REFS0);		// AVCC를 기준 전압으로 선택
	
	ADCSRA |= 0x07;				// 분주비 설정
	ADCSRA |= (1 << ADEN);		// ADC 활성화
	ADCSRA |= (1 << ADFR);		// 프리 러닝 모드
	
	ADMUX |= ((ADMUX & 0xE0) | channel);	// 채널 선택
	ADCSRA |= (1 << ADSC);					// 변환 시작
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));			// 변환 종료 대기
	
	return ADC;								// 10비트 값을 반환
}

int main(void)
{
	int read;
	
	stdout = &OUTPUT;					// printf 사용 설정
	stdin = &INPUT;						// scanf 사용 설정
	
	UART1_init();						// UART1 초기화
	UART0_init();						// UART0 초기화
	ADC_init(0);						// ADC 초기화
	
	UCSR0B |= (1 << RXCIE0);			// 송신 가능 대기
	sei();								// 전역적으로 인터럽트 허용
	
	
	while (1)
	{
		// 반복 실행 부분
		read = read_ADC();
		
	}
	
	return 0;
}
