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
void writeChar(char x);
void writeString(char st[]);
void initUsart();
void writeInt(int i);


volatile int knopingedrukt = 0;
volatile int bingus = 15;



ISR(INT1_vect){
	//knopingedrukt = 1;
	knopingedrukt = !knopingedrukt;}

ISR(USART_RX_vect){
bingus = UDR0-48;
	
}

int main(void)
{
//int bingus = 16;
DDRB=0xFF;
initUsart();
initportD();
   while (1)
    {
		

/*	if(knopingedrukt){
	PORTB = (1<<PORTB1) | (1<<PORTB3) | 1<<PORTB4;
		_delay_ms(100);
		PORTB ^= 1<<PORTB4;
		_delay_ms(900);
		}
	else {
		PORTB = 1<<PORTB0 | 1<<PORTB2| 1<<PORTB4;
		_delay_ms(100);
		PORTB ^= 1<<PORTB4;
		_delay_ms(900);
    }
	}*/
	while(bingus>-1 && knopingedrukt==0){
		PORTB = bingus|1<<PORTB4;
		bingus--;
		_delay_ms(500);
		PORTB ^= 1<<PORTB4;
		_delay_ms(500);
		writeString("potato");
		writeInt(bingus);		
		writeString("\r\n");
	}
	if (bingus == -1){bingus = 16;}
	
}
}
void initportD(){
	DDRD = 00;
	PORTD |= 1 << PORTD3; //pull-up
 	EICRA |= 1 << ISC11;
 	EIMSK |= 1 << INT1;
	sei();
}

void writeString(char st[]) {
	for(uint8_t i = 0 ; st[i] !=0; i++) {
		writeChar( st[i] );
		
	}
}

void writeChar(char x){
	while(~UCSR0A & (1 << UDRE0));
	UDR0 = x;
}

void initUsart(){
	UCSR0A |= 0;
	UCSR0B |= (1 << TXEN0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00) | (1<<UPM00);
	UBRR0H=00;
	UBRR0L=103;
}
 
uint8_t knopDxIngedrukt(uint8_t knop){
	_delay_ms(70);
	if(~PIND & (1 << knop)) return 1;
	else return 0; 
}

void writeInt(int i) {
char buffer[8];
itoa(i,buffer,10);
writeString(buffer);
}

