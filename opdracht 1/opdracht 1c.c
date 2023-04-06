/*
 * opdracht 3 looplicht week 1.c
 *
 * Created: 2-3-2022 05:58:39
 * Author : Aronh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

// uint8_t antidender(void) {
// 	if(~PINB & (1<<PORTB7)){
// 		_delay_ms(200);
// 		if(~PINB & (1 << PORTB7))
// 		return 1;
// 	}
// 	return 0;
// }

void zetLedUit( int sw){
PORTD ^= (1 << sw);
}
void zetLedAan( int sw){
PORTD ^= (1 << sw);
}

int main(void)
{
	DDRB = 0xFF;
	DDRD = 0xFF;
	PORTB |= 1 << PORTB7; //initialiseer PORTB
	int sw = 0;
	while (1)
	{
		//if(antidender()){
			//while(~PINB & (1 << PORTB7)){zetLedAan();}
		//}
		//if(antidender()){
		//zetLedUit();
		//}
		for(sw = 0; sw<8; sw++){zetLedAan(sw);
		 _delay_ms(200);
		zetLedUit(sw);
		_delay_ms(200);}
		PORTB ^= (1 << PORTB0);
		_delay_ms(200);
		PORTB ^= (1 << PORTB0);
		_delay_ms(200);
		PORTB ^= (1 << PORTB1);
		_delay_ms(200);
		PORTB ^= (1 << PORTB1);
		
		
	}
	return 0;
}


