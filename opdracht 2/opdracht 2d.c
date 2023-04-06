/*
 * week 2 opdracht 4.c
 *
 * Created: 11-3-2022 10:18:19
 * Author : Aronh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void writeChar(char x);
void writeString(char st[]);
void initUsart();
char readChar();
void zetLedB0_B3(uint8_t x);

int main(void)
{	
	DDRB = 0xFF;
	char x;
	initUsart();
    PORTB = 0;
	writeChar('\f');
    while (1) 
    {
	writeString("zet een HEX waarde op de the pinnen B0...B3: ");
	x = readChar();
	writeChar(x);
	writeString("\r\n");
	writeChar(x);
	writeString("\r\n");
	zetLedB0_B3(x);
	
    }
}

void zetLedB0_B3(uint8_t x){
if (x>59){x = x-55;}
else{x = x-48;}
PORTB = x;
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

void writeString(char st[]) {
	for(uint8_t i = 0 ; st[i] != 0 ; i++) {
		writeChar( st[i] );
	}
}

void writeChar(char x){
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}

void initUsart(){
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0) | (1<<RXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (UPM00 <<1);
	UBRR0H=00;
	UBRR0L=103;
}

