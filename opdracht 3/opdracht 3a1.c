/*
 * opdracht week 3 a1.c
 *
 * Created: 23-3-2022 10:01:33
 * Author : Aronh
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initportD();
uint8_t knopDxIngedrukt(uint8_t knop);
volatile uint8_t ingedrukt = 0;


int main(void)
{
DDRB=0xFF;
initportD();
    while (1)
	
    {
	if(knopDxIngedrukt(PIND3))
		PORTB = 1 << PORTB1 | 1 << PORTB3;
	else 
		PORTB = 1 << PORTB0 | 1 << PORTB2;
    }
}

void initportD(){
	DDRD = 00;
	PORTD = 1 << PORTD3;
	//EICRA = 1 << ISC00;
	//EIMSK = 1 << INT0;
	//sei();
}
 
uint8_t knopDxIngedrukt(uint8_t knop){
	_delay_ms(70);
	if(~PIND & (1 << knop)) return 1;
	else return 0; 
}