#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>



int GetKey(void);
void USART1_initTransmit(void);
void USART1_sendChar(char data);
void USART1_sendString(string data);
void USART1_initRecieve(void);
char USART1_recieveChar(void);


int main(void){
    char digit[20]={'1','2','3','A','5','6','B','7','8','9','C','0','*','0','#','D','\0'};
    int key;
    DDRD=0x00;
    DDRA = 0xFF;
    DDRC=0x00;
    DDRB=0x08;
    DDRB &= ~(1<<PB0);
    
    USART1_initTransmit();
    USART1_initRecieve();
    char PIN[4];
    while(1){


        key = getKey();

        if (key!=16){
        
            USART0_sendChar(digit[key]);

            

        }
        
        pass_match_status=USART1_recieveChar()

        if (pass_match_status=='1'){
            PORTA=0b11000000;
        }
        else{
            PORTA=0b11000110;
        }
        //pushButton();

        }


    }


int GetKey(void){
    char x;
    int data;
    x=PINC;
    if(x==0x01){
        data=(PIND && 0x0f);
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
        UDR0=data;
        _delay_ms(100);
    }
}
void USART1_sendString(char *data)
{
    while(*data!='\0')
    {
        USART0_sendChar(*data);
        data++;
    }
}

void USART1_initRecieve(void){

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

// void pushButton(){
// 	char x = PINB;
// 	char y = x & 0b00000001;
//     if(y==0){
//         PORTA=0b11000110;
//     }
//     else{
//         PORTA=0b11000000;
//     }