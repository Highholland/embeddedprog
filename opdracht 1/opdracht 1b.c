/*
 * opdracht 2 week1.c
 *
 * Created: 1-3-2022 18:59:55
 * Author : Aronh
 */ 


#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

uint8_t antidender(void) {
	if(~PINB & (1<<PORTB7)){
		_delay_ms(200);
		if(~PINB & (1 << PORTB7))
		return 1;
	}
	return 0;
}

//void zetLedUit(){
	//PORTB ^= (1 << PORTB5);
//}
void zetLedAan(){
	PORTB ^= (1 << PORTB5);
}

int main(void)
{
DDRB = 1 << PORTB5;
PORTB |= 1 << PORTB7; //initialiseer PORTB
int sw = 0;
while (1)
{
if(antidender()){
	while(~PINB & (1 << PORTB7)){zetLedAan();}
	}
//if(antidender()){
	//zetLedUit();
//}
	
}
return 0;
}


