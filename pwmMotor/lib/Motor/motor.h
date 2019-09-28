#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>

#ifndef __MOTOR_H
#define __MOTOR_H
#endif

/*
Pins

Wheel 1
Dir: D13
Pwm: C6

Wheel 2
Dir: d11
Pwm: d15

Wheel 3
Dir: b11
Pwm: b15

Wheel 4
Dir: e14
Pwm: b13

Wheel 5
Dir: c4
Pwm: a5

Wheel 6
Dir: a2
Pwm: a4
*/

const static int numMotors = 6;

GPIO_TypeDef* PwmGPIO[numMotors] = {GPIOD, GPIOD, GPIOB, GPIOE, GPIOC, GPIOA};
GPIO_TypeDef* DirGPIO[numMotors] = {GPIOC, GPIOD, GPIOB, GPIOB, GPIOA, GPIOA};

uint16_t dir[numMotors] = {GPIO_Pin_13, GPIO_Pin_11, GPIO_Pin_11,
                           GPIO_Pin_14, GPIO_Pin_4,  GPIO_Pin_2};
uint16_t pwm[numMotors] = {GPIO_Pin_6,  GPIO_Pin_15, GPIO_Pin_15,
                           GPIO_Pin_13, GPIO_Pin_5,  GPIO_Pin_4};

// TODO: Add timer array (of size 6) if multiple timers are used

enum statusLed { ERROR = 8, OK, HALT };

public:
enum Direction { STOP, FORWARD, RIGHT, BACKWARD, LEFT };
// Initialization Functions
void InitializeTimer();
void intializeWheels();

// Control motor by selecting
// wheelNumber as index, speed and direction
void controlWheel(const int index, const int speed, const int direct);

// Takes a direction from enum Direction
// to move all motors to a particular direction
void moveRover(const enum Direction dir);

// Sets all dir and pwm to 0
// Required to start Cytron
void resetAll();
