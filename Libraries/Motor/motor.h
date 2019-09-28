#ifndef __MOTOR_H
#define __MOTOR_H
#endif

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP 0
#define FORWARD 1
#define RIGHT 2
#define BACKWARD 3
#define LEFT 4
#define numMotors 6

/*
Pins

Wheel 1 	Wheel 2 	Wheel 3
Dir: D13 	Dir: d11 	Dir: b11
Pwm: C6 	Pwm: d15 	Pwm: b15

Wheel 4 	Wheel 5 	Wheel 6
Dir: e14 	Dir: a5 	Dir: f4
Pwm: b13 	Pwm: b1 	Pwm: a7

*/

typedef struct motorStruct Motor;

struct motorStruct {
  int currentState;

  // Direction GPIO Port and Pins
  GPIO_TypeDef* DirGPIO[numMotors];
  uint16_t dir[numMotors];

  // PWM GPIO Ports and Pins
  GPIO_TypeDef* PwmGPIO[numMotors];
  uint16_t pwm[numMotors];

  /* Timer */
  uint32_t timPeriod;
  uint32_t timPrescaler;
};

void motorInit(Motor* motor);

// Initialization Functions
void InitializeTimer(Motor* motor);
void IntializeWheels(Motor* motor);


// Control motor by selecting
// wheelNumber as index, speed and direction
void controlWheel(Motor* motor, const int index, const int speed,
                  const int direct);

// Takes a direction from enum Direction
// to move all motors to a particular direction
void moveRover(Motor* motor, int dir);

// Sets all dir and pwm to 0
// Required to start Cytron
void resetAll(Motor* motor);
