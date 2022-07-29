/*
 * Receiver.c
 *
 * Created: 7/26/2022 1:58:23 PM
 * Author : TLS
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>
#include<string.h>

void USART1_config(void);
char USART1_recieveChar(void);
char * USART1_recievePass();
void USART1_sendStatus(char data);

int main(void){
	DDRB |= 1<<PB0; // declaring PB0 as op pin for OCO 
	// Initializing timer for servo
	TCCR0 &= ~(1<<FOC0); // FOC0 is 0 for PWM mode
	TCCR0 |= (1<<WGM01)|(1<<WGM00);
	TCCR0 |= (1<<CS01)|(1<<CS00);
	TCCR0 |= (1<<COM01);
	OCR0 = 23;
	
	DDRC = 0xff; // for debugging
	
	char latch_status = 2;		// latch is closed initially
	
	// USART1
	DDRB |= 1<<PB3;		// PB3 as op for Tx
	DDRB &= ~(1<<PB2);	// PB2 as ip for Rx	
	PORTB |= (1<<PB2);	// For error checking
	USART1_config();
	
	char PIN[5]={3, 3 , 3, 3,'\0'};
	while(1){
		char PINattempt[5];
			_delay_ms(100);
		//PORTC=latch_status;
		PORTC=latch_status;
		USART1_sendStatus(latch_status);
		//_delay_ms(1000);
		
		if (latch_status==2){
			//PORTC=0xff;
					// latch is closed so compare the pass
			strcpy(PINattempt,USART1_recievePass());	// PINattempt = USART1_recievePass() = Entered pass
			//PORTC=0b11111111;
			int i;
			//for(i=0;i<5;i++){
				//PORTC=PINattempt[i];
				//_delay_ms(5000);
			//}
			
			if(!(strcmp(PINattempt,PIN))){ // pass matched
				latch_status=1; // opening the latch
				OCR0 = 35;
			}
 		
 			}
			else{
				
 				while(USART1_recieveChar()!=3); // push button not pressed
					 //PORTC=0b10101010;
 					latch_status=2;
					 OCR0=23;
 					
			}
		}
	}
	

void USART1_config(void)          // to configure USART1
{
	UBRR1H=0x00;
	UBRR1L=0x05;
	UCSR1B|=(1<<RXEN1)|(1<<TXEN1);
	UCSR1C|=(1<<USBS1)|(3<<UCSZ10);
}


char * USART1_recievePass(void){
	USART1_sendStatus(2);
	char recieved_data;
	static char PIN[5]={};
	PIN[4]='\0';
	int PINlength = 0;
	while(PINlength<4){
			recieved_data=USART1_recieveChar();
			PORTC=recieved_data;
			PIN[PINlength]=recieved_data;
			PINlength=PINlength+1;
			USART1_sendStatus(2);
			_delay_ms(100);
		}
		
	return PIN;
}

char USART1_recieveChar(void){          // function to receive a character of pass
	unsigned char recieved_data;
	
	while(!(UCSR1A&(1<<RXC1)));
	recieved_data=UDR1;
	_delay_ms(50);
	
	return recieved_data;
}

void USART1_sendStatus(char data){
	while(!(UCSR1A&(1<<UDRE1)));
	UDR1=data;
	char x = data;
	//PORTC = x;
	_delay_ms(50);
}