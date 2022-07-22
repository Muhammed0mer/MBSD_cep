#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

int GetKey(void);
string wait_for_pin(void);

int main(void){
    char digit[20]={'1','2','3','A','5','6','B','7','8','9','C','0','*','0','#','D','\0'};
    int key;
    DDRD=0xf0;
    DDRA=0xff;
    DDRC=0x00;
    DDRB=(1<<PINB0);
    PORTA=digit[16];
    while(1){
        key = getKey();

        if (key!=16){
            PORTA=digit[key];
        }
    }

}
int GetKey(void){
    char x;
    PORTB=0x00;
    int data;
    x=PINC;
    if(x==0x01){
        data=(PIND&0x0f);
        return data;
    }
    return 16;
}
char() wait_for_pin(void){
    string pin;
    while(1){
        pin 
    }
}
void USART0_initTransmit(void)
{
DDRD |= (1<<PD1);
DDRD &= ~(1<<PD0);
PORTD |= (1<<PD0);
DDRA=0x00;
UBRR0H=0x00;
UBRR0L=0x05;
UCSR0B=(1<<TXEN0);
UCSR0C=(3<<UCSZ00)|(1<<USBS0);
}
void USART0_sendChar(char data)
{
char y = 0;
    y=PINA & 0x01;
    if(y==0){
        while(!(UCSR0A&(1<<UDRE0)));
        UDR0=0xf0;
        _delay_ms(100);
    }
}
void USART0_sendString(char *data)
{
    while(*data!='\0')
    {
        USART0_sendChar(*data);
        data++;
    }
}

