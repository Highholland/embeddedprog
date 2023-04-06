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
volatile int knopingedrukt =0;
ISR(INT1_vect){
	//knopingedrukt = 1;
	knopingedrukt = !knopingedrukt;

}

int main(void)
{
int ledstatus = 0;
DDRB=0xFF;
initportD();
    while (1)
    {
	if(knopingedrukt){
	PORTB = (1<<PORTB1) | (1<<PORTB3);
		_delay_ms(70);}
	else {
		PORTB = 1<<PORTB0 | 1<<PORTB2;
    }
	}
}

void initportD(){
	DDRD = 00;
	PORTD = 1 << PORTD3; //pull-up
	EICRA = 1 << ISC10;
	EIMSK = 1 << INT1;
	sei();
}
 
uint8_t knopDxIngedrukt(uint8_t knop){
	_delay_ms(70);
	if(~PIND & (1 << knop)) return 1;
	else return 0; 
}

