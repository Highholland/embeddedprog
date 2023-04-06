/*
 * Week 2 opdracht 2.c
 *
 * Created: 11-3-2022 09:29:20
 * Author : Aronh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void) {
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0); // Enable de USART Transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (UPM00 <<1); /* 8 data bits, 1 stop bit */
	UBRR0H=00;
	UBRR0L=103; //baudrade 9600 bij
	while (1) {
		for(char c='0'; c<='9';c++) {
			while(~UCSR0A & (1 << UDRE0));
			UDR0 = c;
			for(uint8_t i=0;i<4;++i)
			_delay_ms(250);
		}
	}
	return (0);
}

/* Deze code laat het verschil zien in 8 en 7 bit en parity mode. 
Als de ontvanger niet goed op deze is ingesteld, komt er alleen maar onzin op het scherm.*/