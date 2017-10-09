#ifndef _PINOUT_H_
#define _PINOUT_H_

// Lights
#define LIGHTS_DDR				DDRB
#define LIGHTS_PORT				PORTB
#define LIGHTS					PB4

// Laser
#define LASER_DDR				DDRB
#define LASER_PORT				PORTB
#define LASER					PB5

// Sensors
#define SENSOR1_DDR				DDRD
#define SENSOR2_DDR				DDRD
#define SENSOR3_DDR				DDRC
#define SENSOR1_PORT			PORTD
#define SENSOR2_PORT			PORTD
#define SENSOR3_PORT			PORTC
#define SENSOR1					PD2
#define SENSOR2					PD3
#define SENSOR3					PC5

// Coils
#define COILS_DDR				DDRC
#define COILS_PORT				PORTC
#define COIL1					PC0
#define COIL2					PC1
#define COIL3					PC2

//Left motor
#define LEFT_MOTOR_DIR_DDR		DDRC
#define LEFT_MOTOR_DIR_PORT		PORTC
#define LEFT_MOTOR_DIR			PC3

#define LEFT_MOTOR_PWM_DDR		DDRD
#define LEFT_MOTOR_PWM_PORT		PORTD
#define LEFT_MOTOR_PWM			PD5			/* OC0B */

//Right motor
#define RIGHT_MOTOR_DIR_DDR		DDRC
#define RIGHT_MOTOR_DIR_PORT	PORTC
#define RIGHT_MOTOR_DIR			PC4

#define RIGHT_MOTOR_PWM_DDR		DDRD
#define RIGHT_MOTOR_PWM_PORT	PORTD
#define RIGHT_MOTOR_PWM			PD6			/* OC0A */

// Vertical servo
#define VERT_SERVO_DDR			DDRB
#define VERT_SERVO_PORT			PORTB
#define VERT_SERVO				PB1			/* OC1A */

// Horizontal servo
#define HORIZ_SERVO_DDR			DDRB
#define HORIZ_SERVO_PORT		PORTB
#define HORIZ_SERVO				PB2			/* OC1B */

#endif	// _PINOUT_H_
