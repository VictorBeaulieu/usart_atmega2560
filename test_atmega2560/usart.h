/*
 * usart.h
 *
 * Created: 16/01/2019 11:29:32
 *  Author: VictorBeaulieu
 */ 

#define CLOCK 16000000
#define RX_BUFFER 128

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart_config.h"
#include "bool.h"

unsigned char msg_from_usart0[RX_BUFFER];
unsigned char msg_from_usart1[RX_BUFFER];
unsigned char RX0_index;
unsigned char RX1_index;

unsigned char RX0_msg_complete;
unsigned char RX1_msg_complete;

void init_usart0(unsigned int bd,unsigned int config);
void init_usart1(unsigned int bd,unsigned int config);

void write_char_usart0(unsigned char c);
void write_char_usart1(unsigned char c);

void send_string_usart0(unsigned char *str);
void send_string_usart1(unsigned char *str);

unsigned char read_char_usart0();
unsigned char read_char_usart1();

void read_string_usart0(unsigned char *str);
void read_string_usart1(unsigned char *str);


