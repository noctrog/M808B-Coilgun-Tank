#include "../includes/Motors.h"

void initMotors()
{
	// set as output and initialize
	LEFT_MOTOR_DIR_DDR |= (1 << LEFT_MOTOR_DIR);
	LEFT_MOTOR_DIR_PORT |= (1 << LEFT_MOTOR_DIR);
	RIGHT_MOTOR_DIR_DDR |= (1 << RIGHT_MOTOR_DIR);
	RIGHT_MOTOR_DIR_PORT |= (1 << RIGHT_MOTOR_DIR);

	LEFT_MOTOR_PWM_DDR |= (1 << LEFT_MOTOR_PWM);
	RIGHT_MOTOR_PWM_DDR |= (1 << RIGHT_MOTOR_PWM);
	//PRR &= ~(1 << PRTIM0);

	// set servos as output
	HORIZ_SERVO_DDR |= (1 << HORIZ_SERVO);
	VERT_SERVO_DDR |= (1 << VERT_SERVO);

	// Timer 0 - tank motors
	//Fast PWM mode (mode 3)
	TCCR0A |= (1<<WGM00) | (1<<WGM01);
	// Clear OC0A on Compare Match, set OC0A at BOTTOM (non-inverting mode)
	TCCR0A |= (1<<COM0A1);
	// Clear OC0B on Compare Match, set OC0B at BOTTOM, (non-inverting mode)
	TCCR0A |= (1<<COM0B1);
	// Clock divide by 256, f = 7372800 -> 28.8 kHz
	TCCR0B |= (1<<CS00);

	// Timer 1 - turret servos
	// Fast PWM (mode 14), counter max in ICR1
	TCCR1A |=(1 << WGM11);
	TCCR1B |= (1<<WGM12) | (1 << WGM13);
	// clear OC1A/OC1B on CompareMatch
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	// 8 prescaling
	TCCR1B |= (1<<CS11);
	// TOP value = 20ms
	ICR1 = 18432;

	// set the turret default position
	// horizontal - middle
	OCR1B = (SERVO_HORIZ_MAX_VALUE + SERVO_MIN_VALUE) / 2;
	// 12 first bits for position, 4 remaining bits for a smooth control
	horizServoPos = ((OCR1B - SERVO_MIN_VALUE) << 4);
	// vertical - down
	OCR1A = SERVO_MIN_VALUE;
	vertServoPos = 0;
}

void refreshLeftMotor(int8_t strength)
{
	/*
	// update direction
	if (direction)
		LEFT_MOTOR_DIR_PORT |= (1<<LEFT_MOTOR_DIR);
	else
		LEFT_MOTOR_DIR_PORT &= ~(1<<LEFT_MOTOR_DIR);
	// update intensity
	OCR0A = strength;
	*/

	if (strength > 0)
		LEFT_MOTOR_DIR_PORT |= (1<<LEFT_MOTOR_DIR);
	else
		LEFT_MOTOR_DIR_PORT &= ~(1<<LEFT_MOTOR_DIR);

	OCR0B = abs(strength*2);
}

void refreshRightMotor(int8_t strength)
{
	// update direction
	if (strength > 0)
		RIGHT_MOTOR_DIR_PORT |= (1<<RIGHT_MOTOR_DIR);
	else
		RIGHT_MOTOR_DIR_PORT &= ~(1<<RIGHT_MOTOR_DIR);
	// update intensity
	OCR0A = abs(strength*2);
}

void refreshHorizontalMotor(int16_t value)
{
	// clamp position
	// if greater than 1737
	if (horizServoPos + value > ((SERVO_HORIZ_MAX_VALUE - SERVO_MIN_VALUE) << 4))
		horizServoPos = ((SERVO_HORIZ_MAX_VALUE - SERVO_MIN_VALUE) << 4);
	// if lower than 0
	else if (horizServoPos < -value)
		horizServoPos = 0;
	else
		horizServoPos += value;

	OCR1B = ((horizServoPos) >> 4) + SERVO_MIN_VALUE;
}

void refreshVerticalMotor(int16_t value)
{
	if (vertServoPos + value > ((SERVO_VERT_MAX_VALUE - SERVO_MIN_VALUE) << 4))
		vertServoPos = ((SERVO_VERT_MAX_VALUE - SERVO_MIN_VALUE) << 4);
	else if (vertServoPos < -value)
		vertServoPos = 0;
	else
		vertServoPos += value;

	OCR1A = ((vertServoPos) >> 4) + SERVO_MIN_VALUE;
}
