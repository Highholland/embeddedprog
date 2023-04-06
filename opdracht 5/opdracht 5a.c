#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void initBlink();
void zetLedAan(uint8_t);
void zetLedUit(uint8_t);
void initUsart();
void wacht1sec();
int main(void)
{
	initUsart();
	initBlink();
	while (1)
	{
		wacht1sec();
		PORTB ^= 1<<PORTB1;
// 		zetLedAan(1);
// 		_delay_ms(500);
// 		zetLedUit(1);
// 		_delay_ms(500);
	}
	return 0;
}
void initBlink() {
	DDRB = 1<<PORTB1;
}
void zetLedAan(uint8_t b) {
	PORTB |= 1<<PORTB1;
	
}
void zetLedUit(uint8_t b) {
	PORTB &= ~(1<<PORTB1);
	
}
void wacht1sec(){
	TCCR1A  = 00;
    TCCR1B  = 1 << CS12 | 1 << CS10;
   TCNT1 = 0;
	        while(TCNT1 < 65000);
		
    
	TCCR1B &=~(1<<CS12|1<<CS11|1<<CS10);


}

void initUsart(){
	UCSR0A |= 0;
	UCSR0B |=  (1<<RXCIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H=00;
	UBRR0L=103;
}

