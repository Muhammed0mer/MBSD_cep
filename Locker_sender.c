/*
 * Transmitter.c
 *
 * Created: 7/26/2022 1:56:22 PM
 * Author : TLS
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>


void USART1_config(void);
void pushButton(void);
int getKey(void);
void USART1_sendChar(char data);
char USART1_recieveChar(void);


int main(void){
	
		
	DDRC=0b00000000; 
	DDRE=0xff;
	// Keypad config
	char digit[20]={1,2,3,'A',4,5,6,'B',7,8,9,'C','*',0,'#','D','\0'};
	int key;
	DDRD=0x00;			// Port D as i/p for keypad
	//DDRC &= ~(1<<PC0);	// PC0 as ip to read 
	
	DDRB |= (1<<PB1);  // PB1 as op to give DE = 0 to DE pin of keypad
	
	// 7 segment config
	DDRA = 0xFF;		// Port A as op for 7 segment
	
	// USART1
	DDRB |= 1<<PB3;		// PB3 as op for Tx
	DDRB &= ~(1<<PB2);	// PB2 as ip for Rx	
	PORTB |= (1<<PB2);	// For error checking
	USART1_config();
	
	DDRB &= ~((1<<PB0));// PB0 as ip for push button 
	
	char latch_status;
	
	int PINlen=0;
	
	char btn;
	_delay_ms(1000);
//	char latch_status = '0'; // initilly latch is closed
//	char PIN[4];

	while(1){
//		PORTA=0b11000000; debugging
	
		latch_status=USART1_recieveChar();
		
		
		if (latch_status==1){		// means latch is open
			PORTA=0b11000000;
			PINlen=0;
			pushButton();
			//latch_status=2;
			USART1_sendChar(3);
		}
		if(latch_status==2){		// means latch is closed
			PORTA=0b11000110;
		
			key=getKey();
			
			//_delay_ms(3000);
					
				
				while((key==16)){
					PORTE=PINlen;
					if (PINlen==4){
						PINlen=0;
						break;
					}
					key=getKey();
				};
					
				if(key!=16){
					
				
				USART1_sendChar(digit[key]);
				PINlen++;
				}
				
		}
		
			
		
	}
}

// to get keypad key pressed position
int getKey(void){
	_delay_ms(100);
	char x;
	int data;

	PORTB &= ~(0b00000010); // PB1 assigned 0 for DE
	
	x = PINC  ;
	
			// if data available
		 
		//if((data>=0 && data<=2)| (data>=4 && data<=6) | (data>=8 && data <=10) | (data==13)){
			if(x==0x01){
						data=(PIND & 0x0f);
						//PORTA=data;
						return data;
						
			}
		
	return 16;
}

// char() wait_for_pin(void){
//     string pin;
//     while(1){
//         pin
//     }
// }

void USART1_config(void)          // to configure USART1
{
	UBRR1H=0x00;
	UBRR1L=0x05;
	UCSR1B|=(1<<TXEN1)|(1<<RXEN1);
	UCSR1C|=(1<<USBS1)|(3<<UCSZ10);
}

void USART1_sendChar(char data){
	while(!(UCSR1A&(1<<UDRE1)));
	
	UDR1=data;
	_delay_ms(100);
}

// void USART1_sendString(char *data)
// {
//     while(*data!='\0')
//     {
//         USART0_sendChar(*data);
//         data++;
//     }
// }

char USART1_recieveChar(void){          // function to receive latch status after pass match from Receiver
	char recieved_data;
	
	while(!(UCSR1A&(1<<RXC1)));
	recieved_data=UDR1;
	

	_delay_ms(100);
	
	return recieved_data;
}

void pushButton(){
	while(1){
		char x = PINB;
		char y = x & 0b00000001; // reading only PBO
		if(y==0){				 // y = 0 means push button is pressed
			break;
		}
		
	}
}
