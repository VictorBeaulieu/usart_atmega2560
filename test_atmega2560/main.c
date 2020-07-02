/*
 * test_atmega2560.c
 *
 * Created: 02/07/2020 17:46:22
 * Author : victor.beaulieu
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include <string.h>

int main(void)
{
    init_usart0(9600,_8N1);
    
    DDRD |= 0xC0;
    send_string_usart0((unsigned char*)"hello world\r\n");

    while (1)
    {
	    if(RX0_msg_complete == 1){
		    
		    send_string_usart0(msg_from_usart0);
		    RX0_msg_complete = 0;
		    RX0_index=0;
	    }
	    _delay_ms(10);
	    
    }
}

