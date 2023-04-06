/*
 * opdracht 1.c
 *
 * Created: 28-2-2022 20:18:22
 * Author : Aronh
 */ 

#define F_CPU 16000000 
#include <avr/io.h>
#include <util/delay.h>

uint8_t antidener(void) {
	if(~PINB & (1<<PORTB7)){
		_delay_ms(200);
		if(~PINB & (1 << PORTB7))
		return 1;
	}
	return 0;
}

void zetLedUit(){
	PORTB ^= (1 << PORTB5);
}
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
if(antidener()){
	if(sw == 1){
	zetLedUit();
	sw = 0;}
else{zetLedAan();
	sw = 1;}
}
}
return 0;
}


