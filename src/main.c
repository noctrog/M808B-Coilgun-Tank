#include <common.h>
#include <util/delay.h>

  /*      ________
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
		_|        |_
       |_|        |_|
         |________|
*/

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
}

// watchdog used to turn off continuously the coils in case something goes wrong
void initWatchdog()
{
	wdt_reset();
	// enable watchdog interrupts
	WDTCSR |= (1 << WDCE) | (1 << WDE);
	// timer overflow every 1.0s
	WDTCSR = (1<<WDIE) | (1 << WDP1) | (1 << WDP2);
}

int main()
{
	wdt_disable();
	// disable interrupts while initializing
	cli();

	initUSART();

	// init peripherals
	initMotors();
	initCannon();
	LASER_DDR |= (1 << LASER);
	LIGHTS_DDR |= (1 << LIGHTS);
	COILS_DDR |= (1 << COIL1) | (1 << COIL2) | (1 << COIL3);

	set_sleep_mode(SLEEP_MODE_IDLE);
	sleep_enable();

	printString("BT funciona!");
	// enable interrupts
	sei();

	while(1)
	{
		sleep_mode();
	}

	//Never reached
	return 0;
}
