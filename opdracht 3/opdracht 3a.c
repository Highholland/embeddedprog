/*
 * Week 3 opdracht 1.c
 *
 * Created: 20-3-2022 22:10:34
 * Author : Aronh
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void initportD();
uint8_t knopDxIngedrukt(PIND3);
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
	DDRD &= ~(1 << PORTD3);
	//EICRA = 1 << ISC00;
	//EIMSK = 1 << INT0;
	//sei();
}

uint8_t knopDxIngedrukt(PIND3){
	_delay_us(100);
	if(~PIND & 1 << PORTD3) return 1;
	else return 0; 
}
