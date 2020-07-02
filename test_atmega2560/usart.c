/*
 * usart.c
 *
 * Created: 16/01/2019 11:29:15
 *  Author: VictorBeaulieu
 */ 


#include "usart.h"

void init_usart0(unsigned int bd,unsigned int config){
	unsigned int ubrr = (CLOCK / 16/bd)-1;
	
	unsigned char data_size = config / 100;
	unsigned char parity = (config % 100)/10;
	unsigned char stop_bit = (config % 100)%10;
	
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	
	UCSR0A = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x00;
	
	switch (data_size)
	{
		case 5:
			UCSR0C &= 0xF9;
			break;
		case 6:
			UCSR0C |= 0x02;
			break;
		case 7:
			UCSR0C |= 0x04;
			break;
		case 8:
			UCSR0C |= 0x06;
			break;
	}
	switch (parity)
	{
		case 0:
			UCSR0C &= 0xCF;
			break;
		case 1:
			UCSR0C |= 0x20;
			break;
		case 2:
			UCSR0C |= 0x60;
			break;		
	}
	switch (stop_bit)
	{
		case 1:
			UCSR0C &= 0xF7;
			break;
		case 2:
			UCSR0C |= 0x08;
			break;
	}
	RX0_index=0;
	RX0_msg_complete = FALSE;
	sei();
}

void init_usart1(unsigned int bd,unsigned int config){
	unsigned int ubrr = (CLOCK / 16/bd)-1;
	
	unsigned char data_size = config / 100;
	unsigned char parity = (config % 100)/10;
	unsigned char stop_bit = (config % 100)%10;
	
	UBRR1H = (unsigned char) (ubrr >> 8);
	UBRR1L = (unsigned char) ubrr;
	
	UCSR1A = 0x00;
	UCSR1B = 0x98;
	UCSR1C = 0x00;
	
	switch (data_size)
	{
		case 5:
			UCSR1C &= 0xF9;
			break;
		case 6:
			UCSR1C |= 0x02;
			break;
		case 7:
			UCSR1C |= 0x04;
			break;
		case 8:
			UCSR1C |= 0x06;
			break;
	}
	switch (parity)
	{
		case 0:
			UCSR1C &= 0xCF;
			break;
		case 1:
			UCSR1C |= 0x20;
			break;
		case 2:
			UCSR1C |= 0x60;
			break;
	}
	switch (stop_bit)
	{
		case 1:
			UCSR1C &= 0xF7;
			break;
		case 2:
			UCSR1C |= 0x08;
			break;
	}
	RX1_index=0;
	RX1_msg_complete = FALSE;
	sei();
}

void write_char_usart0(unsigned char c){
	while((UCSR0A & 0x20)==0);
	UDR0 = c;
}

void write_char_usart1(unsigned char c){
	while((UCSR1A & 0x20)==0);
	UDR1 = c;
}

void send_string_usart0(unsigned char *str){
	unsigned char i = 0;
	while(str[i] != 0)
	{
		write_char_usart0(str[i]);
		i++;
	}
}

void send_string_usart1(unsigned char *str){
	unsigned char i = 0;
	while(str[i] != 0)
	{
		write_char_usart1(str[i]);
		i++;
	}
}

unsigned char read_char_usart0(){
	while (!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

unsigned char read_char_usart1(){
	return UDR1;
}


ISR(USART0_RX_vect){

	unsigned char c;
	while (!(UCSR0A & (1<<RXC0)));
	c = UDR0;
	msg_from_usart0[RX0_index] = c;
	RX0_index++;
	
	RX0_msg_complete = TRUE;
	
	/*		
	if((UCSR0A & 0x80) == 0)
	{
		;
		RX0_index=0;
	}
	*/
	
}

ISR(USART1_RX_vect){
	
}