#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define NOTE_D 293.66
#define NOTE_Ds 311.13
#define NOTE_F 349.23
#define NOTE_G 392
#define TestTIJDSDUUR1 1800
#define TestTIJDSDUUR2 1200

void wacht1sec();
void playBeethoven();
void rust(uint16_t v);
void initialisatie();
void playNoot(float freq, uint16_t tijd);


int main(void)
{initialisatie();																																																																																																		
while (1)
{
//  TCCR1A = (1<<COM1B0);
//  OCR1A = 16000000/(NOTE_D *2)-1;//*2 want ctc toggle mode
//  rust(TestTIJDSDUUR1);
//  TCCR1A = 0;
//  rust(TestTIJDSDUUR2);
// OCR1A = 45*256;
// TCCR1A = (1<<COM1B0);
//  rust(TestTIJDSDUUR1);
//    TCCR1A = 0;
//  rust(TestTIJDSDUUR2);
playBeethoven();

}
}

void playNoot(float freq, uint16_t tijd){
	TCCR1A = (1<<COM1B0);
	OCR1A = 16000000/(freq *2)-1;
	rust(tijd);
	TCCR1A = 0;
	
}

void initialisatie(){
DDRB |= (1<<PORTB2);// het genereren van een toon gebeurd op een output
TCCR1A |= (1<<COM1B0); 
TCCR1B |= (1<<CS10)|(1<<WGM12);	//CTC
}
void rust(uint16_t v) {
     for(uint16_t i=0; i< v; ++i)
          _delay_us(100);
}

void wacht1sec(){
	TCCR1A  = 00;
	TCCR1B  = 1 << CS12 | 1 << CS10;
	TCNT1 = 0;
	while(TCNT1 < 65000);
	TCCR1B &=~(1<<CS12|1<<CS11|1<<CS10);
}

void playBeethoven(){
	playNoot(NOTE_G, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_G, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_G, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);	
	playNoot(NOTE_Ds, TestTIJDSDUUR1*4);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_F, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_F, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);
	playNoot(NOTE_F, TestTIJDSDUUR1);
	rust(TestTIJDSDUUR2);	
	playNoot(NOTE_D, TestTIJDSDUUR1*4);
	rust(TestTIJDSDUUR2);
}


