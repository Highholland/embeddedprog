/*
 * opdracht 1 week 2.c
 *
 * Created: 3-3-2022 01:12:15
 * Author : Aronh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void writeChar(char x);
void writeString(char st[]);
void writeInt(int i);

int main(void) {
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0); // Enable de USART Transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
	UBRR0H=00;
	UBRR0L=103; //baudrade 9600 bij
	while (1) {
		for(int c=1; c<=100;c++) {
			writeInt(c);
			for(uint8_t i=0;i<4;++i)
			_delay_ms(250);
		}
	}
	return 0;}
//while(1) {
//B  writeChar('1');
//B  writeChar('2');
//B  writeChar('3');
//B  writeChar('4');
//C  writeString("Hallo");
//D  writeInt(1234);
//D  for(uint8_t i=0;i<4;++i)

void writeInt(int i) {
 char buffer[8];
 itoa(i,buffer,10);
 writeString(buffer);
 writeString("   ");
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

