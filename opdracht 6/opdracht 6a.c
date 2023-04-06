/*
 * week opdracyt 6a.c
 *
 * Created: 20-4-2022 19:56:55
 * Author : Aronh
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void dimLed(uint8_t t);
void initTimer2FastPWM();
// void initAD();
// int leesADwaarde(uint8_t);


int main(void)
{
  initTimer2FastPWM();
  _delay_ms(1000);
  dimLed(50);
  _delay_ms(1000);
    while (1) 
    {
	dimLed(10);
	_delay_ms(500);
	dimLed(220);
	_delay_ms(500);
    }
	return 0;
}

void initTimer2FastPWM(){
	DDRD |= (1<<PORTD3); //data direction register
	TCCR2A |= (1<<WGM20) | (1<<WGM21); //counter mode
	TCCR2B |= (1<<CS20); //prescaler 1
}

void dimLed(uint8_t t){
	TCCR2A |= (1<<COM2B1); //timer aanzetten
	OCR2B = t; //duty cylce zetten
}

// void initAD(){
//  /* reference voltage on AVCC */
// 	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
// 	ADCSRA |= (1 << ADEN); 
// }

// int leesADwaarde(uint8_t analoogInput){
// ADCSRA |= (1 << ADSC | 1 << ADIF);
// while(~ADCSRA & (1 << ADIF));
// ADMUX = analoogInput+64;
// return ADC;
// }