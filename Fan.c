#include<avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
unsigned char time = 0;
unsigned char speed = 1;
unsigned char intial_speed = 127;
unsigned short int  count = 0;

void PWM (unsigned char speed_motor){
	OCR0 = speed_motor;
	TCCR0 |= (1<<WGM00) | (1<<WGM01) | (1<<COM01) |(1<<CS01);
	TCNT0 = 0;
	DDRB |=(1<<PB3);
}
int main(){

	DDRC = 0x03;
	DDRD |=(1<<PD7);
	PORTD &=~ (1<<7);
	DDRA = 0x00;
	PORTC = 0x01;
	DDRB = 0x07;
	DDRD = 0x0F;
	PORTD |= 0X01;
	SREG|=(1<<7);
	TCCR2 = (1<<FOC0)|(1<<CS02)|(1<<CS00);
	PORTB &= ~( (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3));
	PWM(intial_speed);
	while(1){

			if(PINA & (1<<PA0)){
			if(speed == 3)
				{
					intial_speed=127;
					speed = 1;
					PWM(intial_speed);
					PORTD = (PORTD & 0xF0) | (speed & 0x0F);
				}
				else
				{
					intial_speed+=62;
					PWM(intial_speed);
					speed++;
					PORTD = (PORTD & 0xF0) | (speed & 0x0F);
				}while(PINA &(1<<PA0));
		}
			if(PINA & (1<<PA1)){
			if(time == 4)
				{
					time = 0;
					PORTB = (PORTB & 0xF0) | (time & 0x0F);
				}
				else
				{
					time++;
					PORTB = (PORTB & 0xF0) | (time & 0x0F);

				}while(PINA &(1<<PA1));
		}
			if(time == 1){
				TIMSK |=(1<<TOIE2);
				if(count == 100){
						//speed = 0;
						//PORTD = (PORTD & 0xF0) | (speed & 0x0F);
						PORTD =0x00;
						TIMSK &=~(1<<TOIE2);
						PWM(0);
						time = 0;
						PORTB = (PORTB & 0xF0) | (time & 0x0F);
						count = 0;
					}
			}


			if(time == 2){
			TIMSK |=(1<<TOIE2);
			if(count == 2000){
				//speed = 0;
				//PORTD = (PORTD & 0xF0) | (speed & 0x0F);
				PORTD =0x00;
				PWM(0);
				time = 0;
				PORTB = (PORTB & 0xF0) | (time & 0x0F);
				TIMSK &=~(1<<TOIE2);
				count = 0;

			}

		} if(time == 3){
			TIMSK |=(1<<TOIE2);
			if(count == 3000){
				//speed = 0;
				//PORTD = (PORTD & 0xF0) | (speed & 0x0F);
				PORTD =0x00;
				PWM(0);
				time = 0;
				PORTB = (PORTB & 0xF0) | (time & 0x0F);
				TIMSK &=~(1<<TOIE2);
				count = 0;

			}

		}if(time == 4){
			TIMSK |=(1<<TOIE2);
			if(count == 4000){
				//speed = 0;
				//PORTD = (PORTD & 0xF0) | (speed & 0x0F);
				PORTD =0x00;

				PWM(0);
				time = 0;
				PORTB = (PORTB & 0xF0) | (time & 0x0F);
				TIMSK &=~(1<<TOIE2);
				count = 0;

			}

		}
		if(PINA & (1<<PA2)){
			//speed = 0;
			time = 0;
			count = 0;
			PORTD =0x00;
			PORTB =0x00;
			PWM(0);
		}while(PINA &(1<<PA2));



	}
}
ISR(TIMER2_OVF_vect){
	count ++;
}
