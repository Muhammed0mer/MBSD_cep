#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

void USART1_initRecieve(void);
void USART1_recieveChar(char data);
void USART1_recievePIN(string data);

void main(void){
    DDRB=0x08;
    USART1_initRecieve();
    char PIN[4]=['0','0','0','\0'];
    while(1){
        PINattempt=USART1_recievePIN();
        if(PINattempt==PIN){
            PORTB=0x08;
        }
        else{
            PORTB=0x00;
        }
    }

}

void USART1_initRecieve(void){
DDRA=0xff;
DDRC=0xff;
UBRR1H=0x00;
UBRR1L=0x05;
UCSR1B=(1<<RXEN1);
UCSR1C=(3<<UCSZ00)|(1<<USBS0);
}
char USART0_recieveChar(void){
    unsigned char recieved_data;
    recieved_data=0;
    while(!(UCSR0A&(1<<UDRE0)));
    recieved_data=UDR0;    
    _delay_ms(100);
    return recieved_data;
    }

const *char USART0_recievePIN(void){
    unsigned char recieved_data = USART0_recieveChar;
    char PIN[4];
    int PINlength = 0;
    while(PINlength<=4){
        if(recieved_data=='#'){
            PINlength=0;
        }
        else{
            PIN[PINlength]=recieved_data;
            PINlength++;
            recieved_data=USART0_recieveChar;
        }
    return PIN;
    }
    recieved_data=UDR0;    
    _delay_ms(100);
    return recieved_data;
    }

    void