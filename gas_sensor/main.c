/*
 * gas_sensor.c
 *
 * Created: 2020-05-03 오후 11:32:23
 * Author : SAMSUNG
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "UART1.h"

FILE OUTPUT \
	= FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT  \
	= FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);
	
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
	
	stdout = &OUTPUT;
	stdin = &INPUT;
	
	UART1_init();
	ADC_init(0);
	
	while(1)
	{
		read = read_ADC();
		
		printf("%d\r\n", read);
		
		_delay_ms(1000);
	}
}

