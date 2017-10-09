#include "common.h"
#include <stdbool.h>

#define SERVO_MIN_VALUE			500
#define SERVO_HORIZ_MAX_VALUE	1737	//2237 - 500
#define SERVO_VERT_MAX_VALUE	980

int16_t horizServoPos;
int16_t vertServoPos;

// init pins and timer0
void initMotors();
// Control left motor
void refreshLeftMotor(int8_t strength);
// Control right motor
void refreshRightMotor(int8_t strength);
// Update the horizontal servo
void refreshHorizontalMotor(int16_t value);
// Update vertical motor
void refreshVerticalMotor(int16_t value);
