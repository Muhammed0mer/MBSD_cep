#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

void USART1_initRecieve(void);
void USART1_recieveChar(char data);
void USART1_recievePIN(string data);
void USART1_initTransmit(void);
void USART1_sendChar(char data);

void main(void){
    char latch_status = '0';
    DDRB=0x08;
    USART1_initTransmit();
    USART1_initRecieve();
    char PIN[4]=['0','0','0','\0'];
    while(1){
        char PINattempt[4];
        if (latch_status=='0'){
            PINattempt=USART1_recievePIN();
            if(PINattempt==PIN){
                latch_status='1';
            }
        else{
            if(USART1_recieveChar()=='1'){
                latch_status='0';  
            }
            }
            USART1_sendChar(latch_status);
        }
        
    }

}

void USART1_initRecieve(void){
DDRA=0xff;
DDRC=0xff;
UBRR1H=0x00;
UBRR1L=0x05;
UCSR1B=(1<<RXEN1);
UCSR1C=(3<<UCSZ10)|(1<<USBS1);
}
char USART1_recieveChar(void){
    unsigned char recieved_data;
    recieved_data=0;
    while(!(UCSR1A&(1<<UDRE1)));
    recieved_data=UDR1;    
    _delay_ms(100);
    return recieved_data;
    }

const *char USART1_recievePIN(void){
    unsigned char recieved_data = USART1_recieveChar;
    char PIN[4];
    int PINlength = 0;
    while(PINlength<=4){
        if(recieved_data=='#'){
            PINlength=0;
        }
        else{
            PIN[PINlength]=recieved_data;
            PINlength++;
            recieved_data=USART1_recieveChar;
        }
    return PIN;
    }
    }

void USART1_initTransmit(void)
{

UBRR1H=0x00;
UBRR1L=0x05;
UCSR1B=(1<<TXEN1);
UCSR1C=(3<<UCSZ10)|(1<<USB10);
}
void USART1_sendChar(char data)
{
char y = 0;
    y=PINA & 0x01;
    if(y==0){
        while(!(UCSR1A&(1<<UDRE1)));
        UDR1=data;
        _delay_ms(100);
    }
}