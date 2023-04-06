#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initBlink();
void zetLedAan(uint8_t);
void zetLedUit(uint8_t);
void initUsart();
void wacht1sec();
void writeChar(char x);
volatile double interupt = 1;
ISR(USART_RX_vect) {
	switch (UDR0-48)
	{
	case 1:
	interupt = 0.5;
		break;
	case 2:
	interupt = 1;
	break;
	case 3:
	interupt = 2;
	break;
	case 4:
	interupt = 100;
	break;
	case 5:
	interupt = 50;
	break;
	}
}
int main(void)
{
	
initUsart();
initBlink();
sei();
while (1)
{
writeChar('b');
wacht1sec();
PORTB ^= 1<<PORTB1;
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
int j,l;
TCCR1A  = 00;
TCCR1B  = 1 << CS12 | 1 << CS10;
TCNT1 = 0;
j = 15625;
l = j / interupt;
while(TCNT1 < l);
TCCR1B &=~(1<<CS12|1<<CS11|1<<CS10);
}

void initUsart(){
	UCSR0A |= 0;
	UCSR0B |= (1 << TXEN0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00) | (1<<UPM00);
	UBRR0H=00;
	UBRR0L=103;
}

void writeChar(char x){
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}



