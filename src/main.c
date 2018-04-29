#define DEBUG
#include "../includes/common.h"
#include <util/delay.h>

#define F_CPU 7372800

ISR(USART_RX_vect)
{
	uint8_t firstByte = UDR0;
	UDR0 = firstByte;

	// Msg that controls lights, laser or firing
	if (firstByte != '@')
	{
		switch(firstByte)
		{
			// Laser On
			case 'L':
				LASER_PORT |= (1 << LASER);
				break;

			// Laser Off
			case 'l':
				LASER_PORT &= ~(1 << LASER);
				break;

			// Lights On
			case 'A':
				LIGHTS_PORT |= (1 << LIGHTS);
				break;

			// Lifhts Off
			case 'a':
				LASER_PORT &= ~(1 << LIGHTS);
				break;

			// Fire
			case 'F':
				// Reset watchdog
				wdt_reset();
				// Turn on first coil
				COILS_PORT |= (1 <<COIL1);
				// Turn on first sensor
				EIMSK |= (1 << INT0);
#ifdef DEBUG
				printString("Bobina 1\n");
#endif
				break;
		}
	}
	// Msg that controls motors
	else
	{
		int8_t left, right, vertical, horizontal;

		// DC motors
		left = receiveByte();
		right = receiveByte();

		// Servos
		horizontal = receiveByte();
		vertical = receiveByte();

		refreshLeftMotor(left);
		refreshRightMotor(right);

		refreshHorizontalMotor(5*horizontal);
		refreshVerticalMotor(-5*vertical);
	}
}

// watchdog interrupt
ISR(WDT_vect)
{
	// turn off all coils
	COILS_PORT &= ~((1 << COIL1) | (1 << COIL2) | (1 << COIL3));

	// Turn off all sensors
	EIMSK &= ~(1 << INT0);
	EIMSK &= ~(1 << INT1);
	PCICR &= ~(1 << PCIE0);
	PCMSK0 &= ~(1 << PCINT5);

	// re configure watchdog
	WDTCSR |= (1 << WDIE);

	// debug
	printString("Watchdog\n");
}

// watchdog used to turn off continuously the coils in case something goes wrong
void initWatchdog()
{
	asm("wdr");

	WDTCSR |= (1<<WDE) | (1<<WDCE);
	WDTCSR = (1<<WDIE) | (1<<WDP2) | (1<<WDP1);
}

int main()
{
    //disable watchdog if enabled
    wdt_reset();
    MCUSR=0;
    WDTCSR|=_BV(WDCE) | _BV(WDE);
    WDTCSR=0;

	// disable interrupts while initializing
	cli();


	// init peripherals
	initUSART();
	initMotors();
	initCannon();
	LASER_DDR |= (1 << LASER);
	LIGHTS_DDR |= (1 << LIGHTS);
	COILS_DDR |= (1 << COIL1) | (1 << COIL2) | (1 << COIL3);

	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();

	printString("BT funciona!");

	// enable interrupts
	initWatchdog();
	sei();

	while(1)
	{
		sleep_mode();
	}

	//Never reached
	return 0;
}
