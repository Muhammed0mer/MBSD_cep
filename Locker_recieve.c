void USART0_initRecieve(void){
DDRD&=~(1<<PD0);
DDRD|=(1<<PD1);
DDRA=0xff;
DDRC=0xff;
UBRR0H=0x00;
UBRR0L=0x05;
UCSR0B=(1<<RXEN0);
UCSR0C=(3<<UCSZ00)|(1<<USBS0);
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
}