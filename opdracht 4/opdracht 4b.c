/*
 * Week opdracht 4b1
 * Author : Aronh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

void writeInt(int i);
void writeChar(char x);
void writeString(char st[]);
void initAD();
int leesADwaarde(int analoogInput);
char readChar();

#define WAARDE1 200

int main(void) {
	initAD();
	uint16_t adcValue, adcValue2;
	
	DDRB=0x10;
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H=00;
	UBRR0L=103;
// 	writeString("Geef de waarde van de port waar de ldr op zit. \r\n");
// 	portldr = readChar() + 16;
// 	writeString("\r\n");
// 	writeInt(portldr);
// 	writeString("\r\nGeef de waarde van de port waar de pmeter op zit. \r\n");
// 	portpmeter = readChar() + 16;
// 	writeString("\r\n");
// 	writeInt(portpmeter);
// 	writeString("\r\n");
	while (1) { /* start ADC conversion */
		adcValue2 = leesADwaarde(4);
		adcValue = leesADwaarde(5); 
		writeInt(adcValue);
		writeString("\r\n");
		writeInt(adcValue2);
		writeString("\r\n");
		if(adcValue + 50 >= adcValue2 && adcValue - 50 <= adcValue2)
		PORTB |=(1 << PORTB4);

		else
		PORTB &= ~(1 << PORTB4);

		_delay_ms(250);
		} /* End event loop */
		return (0); /* This line is never reached */
	}
	
void writeInt(int i){
char buffer[8];
itoa(i,buffer,10);
writeString(buffer);
}

void writeString(char st[]) {
for(uint8_t i = 0 ; st[i] != 0 ; i++) {
writeChar( st[i] );
}
}

void writeChar(char x){
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}

void initAD(){
 /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); 
}

int leesADwaarde(int analoogInput){
ADCSRA |= (1 << ADSC | 1 << ADIF);
while(~ADCSRA & (1 << ADIF));
ADMUX = analoogInput+64;
return ADC;
}

char readChar(){
	char b;
	while (!(UCSR0A & (1<<RXC0)));
	b=UDR0;
	while (~UCSR0A & (1<<UDRE0));
	UDR0=b;
	return b;
	{
	}
}