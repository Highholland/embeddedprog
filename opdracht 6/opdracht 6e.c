/*
 * week opdracht 6d
 *
 * Author : Aronh
 */ 


#define  F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void dimLed();
void initTimer2FastPWM();
void initAD();
int leesADwaarde(uint8_t);
void initTimer1Fast10PWM();
void pasPeriodeTijdTimer1Aan(uint8_t);
void initTimer1fastPWM_IRC();
volatile uint8_t bingus;

ISR(TIMER1_COMPA_vect){
	TCCR2A &= ~(1<<COM2B1); //timer uitzetten
	}

ISR(TIMER1_CAPT_vect){
	TCCR2A |= (1<<COM2B1); //timer aanzetten
}


int main(void)
{ uint8_t periodetijden[]={1,2,3,4,5};
  initTimer2FastPWM();
  initTimer1fastPWM_IRC();
  initAD();
  _delay_ms(1000);
  dimLed(50);
  _delay_ms(1000);
    while (1) 
    {
	long adwaarde = leesADwaarde(5);
	bingus = adwaarde*255/1023;
	dimLed();
    }
	return 0;
}

void initTimer2FastPWM(){
	DDRD |= (1<<PORTD3); //data direction register
	TCCR2A |= (1<<WGM20) | (1<<WGM21); //counter mode
	TCCR2B |= (1<<CS20); //prescaler 1
}

void dimLed(){
	OCR2B = bingus; //duty cylce zetten
}

void initAD(){
 /* reference voltage on AVCC */
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); /* ADC clock prescaler /128 */
	ADCSRA |= (1 << ADEN); 
}

void initTimer1Fast10PWM(){
	DDRB |= (1<<PORTB1);//output portb
	TCCR1A |= (1<<WGM11) | (1<<WGM10); //fast pwm 10bit
	TCCR1B |= (1<<WGM12); //10 bit
	OCR1A = 0x80; //duty cycle 
}

int leesADwaarde(uint8_t analoogInput){
ADCSRA |= (1 << ADSC | 1 << ADIF);
while(~ADCSRA & (1 << ADIF));
ADMUX = analoogInput+64;
return ADC; 
}

void pasPeriodeTijdTimer1Aan(uint8_t getal){  
TCCR1A |= (1<<COM1A1)| (1<<COM1A0); //inverted fast PWM
TCCR1B = (1<< WGM12)|getal; //prescaler veranderen
}


void initTimer1fastPWM_IRC(){
		DDRB |= (1<<PORTB1);//output portb
		TCCR1A |= (1<<WGM11) |(1<<COM1A1);//|(1<<COM1A0); //fast pwm 10bit
		TCCR1B |= (1<<WGM12) | (1<<WGM13);
		TCCR1B |= (1<<CS12) | (1<<CS10); //prescaler
		OCR1A = 32768; //duty cycle
		ICR1 = 65535;
		TIMSK1 |= (1<<OCIE1A) | (1<<ICIE1);
		sei();
}