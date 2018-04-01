#include <avr/io.h>
#include "../includes/USART.h"
#include <util/setbaud.h>

#define BAUD 115200
void initUSART()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
//#if USE_2X
	//UCSR0A |= (1 << U2X0);
//#else
	UCSR0A &= ~(1 << U2X0);
//#endif

	// Enable USART transmitter/receiver
	// 8 data bits, 1 stop bit
	// enable RX complete interrupt
	UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void transmitByte(uint8_t data)
{
	// wait for empty transmit buffer
	loop_until_bit_is_set(UCSR0A, UDRE0);
	// send data
	UDR0 = data;
}

int8_t receiveByte()
{
	// wait for data
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void printString(const char myString[])
{
	uint8_t i = 0;
	while(myString[i])
	{
		transmitByte(myString[i]);
		i++;
	}
}

void readString(char myString[], uint8_t maxLenght)
{
	char dummy;
	uint8_t i = 0;
	for (i = 0; i < (maxLenght - 1); i++)
	{
		dummy = receiveByte();
		//echo
		transmitByte(dummy);
		// store byte in array
		myString[i] = dummy;
	}
	// add a null termination
	myString[i+1] = 0;
}
