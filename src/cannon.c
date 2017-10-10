/*
 * cannon.c
 *
 *  Created on: Oct 9, 2017
 *      Author: Ramon Calvo
 */

#include <common.h>

void initCannon()
{
	// Set sensors to input
	SENSOR1_DDR &= ~(1 << SENSOR1);
	SENSOR2_DDR &= ~(1 << SENSOR2);
	SENSOR3_DDR &= ~(1 << SENSOR3);
	// input no pull up
	SENSOR1_PORT &= ~(1 << SENSOR1);
	SENSOR2_PORT &= ~(1 << SENSOR2);
	// input pull up
	SENSOR3_PORT |= (1 << SENSOR3);

	// Set coils to output
	COILS_DDR |= (1 << COIL1) | (1 << COIL2) | (1 << COIL3);
	// turn off coils
	COILS_PORT &= ~( (1<<COIL1) | (1<<COIL2) | (1<<COIL3) );

	// configure interrupt for sensor1 and sensor2 (INT0 and INT1)
	// no need to enable interrupts here
	// (will be enabled when 'F' is received
	//EIMSK |= (1 << INT0) | (1 << INT1);

	// Trigger INT0 and INT1 on rising edge
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EICRA |= (1 << ISC11) | (1 << ISC10);

	// configure interrupt for sensor3 (PCINT5)
	// (will be enabled by sensor2 interrupt)
	// enable PCICR0 (PCINT0-7)
	//PCICR |= (1 << PCIE0);
	// enable PCINT5 (PC5)
	//PCMSK0 |= (1 << PCINT5);
}

// sensor1 interrupt
ISR(INT0_vect)
{
	// clear watchdog
	wdt_reset();

	// turn off first sensor
	EIMSK &= ~(1 << INT0);
	// turn off first coil
	COILS_PORT &= ~(COIL1);
	// turn on second coil
	COILS_PORT |= COIL2;
	// turn on second sensor
	EIMSK |= (1 << INT1);
}

// sensor2 interrupt
ISR(INT1_vect)
{
	// clear watchdog
	wdt_reset();

	// turn off second sensor
	EIMSK &= ~(1 << INT1);
	// turn off second coil
	COILS_PORT &= ~(1 << COIL2);
	// turn on third coil
	COILS_PORT |= (1 << COIL3);
	// turn on third sensor
	// enable PCICR0 (PCINT0-7)
	PCICR |= (1 << PCIE0);
	// enable PCINT5 (PC5)
	PCMSK0 |= (1 << PCINT5);
}

// sensor3 interrupt
ISR(PCINT0_vect)
{
	// clear watchdog
	wdt_reset();

	// turn off third coil
	COILS_PORT &= ~(1 << COIL3);
	// turn off third sensor
	// disable PCICR0 (PCINT0-7)
	PCICR &= ~(1 << PCIE0);
	// disable PCINT5 (PC5)
	PCMSK0 &= ~(1 << PCINT5);
}
