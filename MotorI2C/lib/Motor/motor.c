#include "motor.h"

void motorInit(Motor* motor) {
  /* Motor values */
  motor->currentState = STOP;
  // motor->numMotors = 6;
  GPIO_TypeDef* dirGpioArr[numMotors] = {GPIOD, GPIOD, GPIOB,
                                         GPIOE, GPIOA, GPIOF};
  uint16_t dir[numMotors] = {GPIO_Pin_13, GPIO_Pin_11, GPIO_Pin_11,
                             GPIO_Pin_14, GPIO_Pin_5,  GPIO_Pin_4};
  GPIO_TypeDef* pwmGpioArr[numMotors] = {GPIOC, GPIOD, GPIOB,
                                         GPIOB, GPIOB, GPIOA};
  uint16_t pwm[numMotors] = {GPIO_Pin_6,  GPIO_Pin_15, GPIO_Pin_15,
                             GPIO_Pin_13, GPIO_Pin_1,  GPIO_Pin_7};

  memcpy(motor->DirGPIO, dirGpioArr, sizeof(motor->DirGPIO));
  memcpy(motor->dir, dir, sizeof(motor->dir));
  memcpy(motor->PwmGPIO, pwmGpioArr, sizeof(motor->PwmGPIO));
  memcpy(motor->pwm, pwm, sizeof(motor->pwm));

  /* Timer Values */
  motor->timPrescaler = 65535 / 4;
  motor->timPeriod = 5;

}

void InitializeTimer(Motor* motor) {
  TIM_Cmd(TIM2, DISABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef timerInitStructure;
  timerInitStructure.TIM_Prescaler = motor->timPrescaler;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // Counting Method
  timerInitStructure.TIM_Period = motor->timPeriod;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  timerInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timerInitStructure);
  TIM_Cmd(TIM2, ENABLE);
}

// TODO: Implement initialization using loops
void IntializeWheels(Motor* motor) {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, ENABLE);

  GPIO_InitTypeDef gpio;
  GPIO_StructInit(&gpio);
  gpio.GPIO_Mode = GPIO_Mode_OUT;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  // gpio.GPIO_PuPd = GPIO_PuPd_DOWN;

  // Initialisation of A port
  gpio.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_Init(GPIOA, &gpio);

  // Initialisation of B port
  gpio.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &gpio);

  // Initialisation of C port
  gpio.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOC, &gpio);

  // Initialisation of D port
  gpio.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_11 | GPIO_Pin_15;
  GPIO_Init(GPIOD, &gpio);

  // Initialisation of D port
  gpio.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOE, &gpio);

  // Initialisation of F port
  gpio.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOF, &gpio);
}

void controlWheel(Motor* motor, const int index, const int speed,
                  const int direct) {

  if (speed == 0) return;
  int timerValue = TIM_GetCounter(TIM2);
  // Speed control
  if (timerValue == 5 - speed)
    GPIO_WriteBit(motor->PwmGPIO[index], motor->pwm[index], Bit_SET);
  else if (timerValue == 5)
    GPIO_WriteBit(motor->PwmGPIO[index], motor->pwm[index], Bit_RESET);

  // Direction control
  if (direct)
    GPIO_WriteBit(motor->DirGPIO[index], motor->dir[index], Bit_SET);
  else
    GPIO_WriteBit(motor->DirGPIO[index], motor->dir[index], Bit_RESET);
}

void moveRover(Motor* motor, int dir) {
  motor->currentState = dir;
  switch (dir) {
    case STOP:
      controlWheel(motor, 0, 0, 0);
      controlWheel(motor, 1, 0, 0);
      controlWheel(motor, 2, 0, 0);
      controlWheel(motor, 3, 0, 0);
      controlWheel(motor, 4, 0, 0);
      controlWheel(motor, 5, 0, 0);
      break;
    case FORWARD:
      // Delay(10);
      controlWheel(motor, 0, 3, 1);
      controlWheel(motor, 1, 3, 1);
      controlWheel(motor, 2, 3, 1);
      controlWheel(motor, 3, 3, 0);
      controlWheel(motor, 4, 3, 0);
      controlWheel(motor, 5, 3, 0);
      break;
    case RIGHT:
      controlWheel(motor, 0, 3, 1);
      controlWheel(motor, 1, 3, 1);
      controlWheel(motor, 2, 3, 0);
      controlWheel(motor, 3, 3, 0);
      controlWheel(motor, 4, 3, 1);
      controlWheel(motor, 5, 3, 1);
      break;
    case BACKWARD:
      controlWheel(motor, 0, 3, 0);
      controlWheel(motor, 1, 3, 0);
      controlWheel(motor, 2, 3, 0);
      controlWheel(motor, 3, 3, 1);
      controlWheel(motor, 4, 3, 1);
      controlWheel(motor, 5, 3, 1);
      break;
    case LEFT:
      controlWheel(motor, 0, 3, 0);
      controlWheel(motor, 1, 3, 0);
      controlWheel(motor, 2, 3, 1);
      controlWheel(motor, 3, 3, 1);
      controlWheel(motor, 4, 3, 0);
      controlWheel(motor, 5, 3, 0);
      break;
    default:
      controlWheel(motor, 0, 0, 0);
      controlWheel(motor, 1, 0, 0);
      controlWheel(motor, 2, 0, 0);
      controlWheel(motor, 3, 0, 0);
      controlWheel(motor, 4, 0, 0);
      controlWheel(motor, 5, 0, 0);
      break;
  }
}

// It should set all dir and pwm to 0
void resetAll(Motor* motor) {
  for (int i = 0; i < numMotors; i++) {
    GPIO_WriteBit(motor->PwmGPIO[i], motor->pwm[i], Bit_RESET);
    GPIO_WriteBit(motor->DirGPIO[i], motor->dir[i], Bit_RESET);
  }
}
