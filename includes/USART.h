//Defines functions to initialize and send/receive data over USART

//include useful macros
#include <avr/sfr_defs.h>
#include <stdint.h>


//If not defined in makefile, set desired baud rate
#ifndef BAUD
#define BAUD 38400
#endif

#define USART_HAS_DATA	bit_is_set(UCSR0A, RXC0)
#define USART_READY		bit_is_set(UCRS0A, UDRE0)

// Takes the defined BAUD and F_CPU,
// calculates the bit-clock multiplier,
// and configures the hardware USART
void initUSART();

// Blocking transmit/receive functions
// When you call these functions, the CPU will hang
// until data comes through
void transmitByte(uint8_t data);
int8_t receiveByte();

// Send string from RAM
void printString(const char myString[]);
// Read string
void readString(char myString[], uint8_t maxLenght);
