#include<stm32f30x.h>
#include<stm32f30x_gpio.h>
#include<stm32f30x_rcc.h>
#include<stm32f30x_tim.h>

#ifndef __MOTOR_H
#define __MOTOR_H
#endif

class Motor{
	private:
		const static int numMotors=2;

		GPIO_TypeDef* PwmGPIO[numMotors] = {GPIOB,  GPIOB};
		GPIO_TypeDef* DirGPIO[numMotors] = {GPIOB,  GPIOE};
		uint16_t dir[numMotors] = {GPIO_Pin_11, GPIO_Pin_14};
		uint16_t pwm[numMotors] = {GPIO_Pin_15, GPIO_Pin_13};

		//TODO: Add timer array (of size 6) if multiple timers are used

		enum statusLed {ERROR=8, OK, HALT};

	public:
		enum Direction {STOP, FORWARD, RIGHT, BACKWARD, LEFT};
		// Initialization Functions
		void InitializeTimer();
		void intializeWheels();

		// Control motor by selecting 
		// wheelNumber as index, speed and direction
		void controlWheel(const int index, const int speed, const int direct);

		// Takes a direction from enum Direction
		// to move all motors to a particular direction
		void moveRover(const Direction dir);

		// Sets all dir and pwm to 0
		// Required to start Cytron
		void resetAll();

};
