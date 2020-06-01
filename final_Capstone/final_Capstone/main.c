/*
 * final_Capstone.c
 *
 * Created: 2020-05-05 오후 11:59:23
 * Author : SAMSUNG
 */ 

#define	F_CPU	16000000L
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART1.h"
#include "UART0.h"

#define MILLIS_INCREMENT_PER_OVERFLOW 1
#define MICROS_INCREMENT_PER_OVERFLOW 24

volatile unsigned long timer0_millis = 0;
volatile int timer0_micros = 0;

FILE OUTPUT \
= FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);

FILE INPUT	\
= FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

ISR(TIMER0_OVF_vect)	// 오버플로 인터럽트
{
	unsigned long m = timer0_millis;
	int f = timer0_micros;
	m += MILLIS_INCREMENT_PER_OVERFLOW;	// 밀리초 단위 시간 증가
	f += MICROS_INCREMENT_PER_OVERFLOW;	// 마이크로초 단위 시간 증가
	
	// 마이크로초가 1,000을 넘어가면 밀리초를 증가시킴
	m += (f/1000);
	f = m % 1000;
	
	timer0_millis = m;
	timer0_micros = f;
}

unsigned long millis()
{
	unsigned long m;
	uint8_t oldSREG = SREG;	// 상태 레지스터 값 저장
	
	cli();		// timer0_millis 값을 읽는 동안 값이 변하지 않도록 인터럽트 비활성화
	
	m = timer0_millis;
	
	SREG = oldSREG;		// 이전 상태 레지스터 값 복원
	
	return m;			// 프로그램 시작 후 경과 시간
}


int main(void)
{
	stdout = &OUTPUT;							// printf 사용 설정
	stdin = &INPUT;								// scanf 사용 설정
	DDRF &= ~0x01;
	
	UART1_init();								// UART1 초기화
	UART0_init();
	
	TCCR0 |= (1 << CS02);	//분주비를 64로 설정
	TIMSK |= (1 << TOIE0);	// 오버플로 인터럽트 허용
	
	sei();				// 전역적으로 인터럽트 허용
	
	int current_pirstate, previous_pirstate;
	unsigned long time_previous, time_current;
	
	time_previous = millis();		// 시작 시간
	previous_pirstate = (PINF & 0x01);
	
	while (1)
	{
		uint8_t data_in;
		time_current = millis();
		current_pirstate = (PINF & 0x01);
		if((previous_pirstate != current_pirstate) || ((time_current - time_previous) > 5000))
		{
			time_previous = time_current;
			previous_pirstate = current_pirstate;
			if(current_pirstate)
				{
					scanf("%c", &data_in);
					UART0_transmit(data_in);
					printf("%c", data_in);
				}
			else
				{
					scanf("%c", &data_in);
					UART0_transmit(data_in);
					printf("%c", data_in);
				}
		}
		
	}

	return 0;

}

