
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>

#define STOP 0
#define FORWARD 1
#define RIGHT 2
#define BACKWARD 3
#define LEFT 4
#define numMotors 6

uint16_t test = GPIO_Pin_6;

int currentState = 0;

void Delay(uint32_t nTime);
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
Dir: a5
Pwm: b1

Wheel 6
Dir: f4
Pwm: a7
*/

// Direction GPIO Port and Pins
GPIO_TypeDef* DirGPIO[numMotors] = {GPIOD, GPIOD, GPIOB, GPIOE, GPIOA, GPIOF};
uint16_t dir[numMotors] = {GPIO_Pin_13, GPIO_Pin_11, GPIO_Pin_11,
                           GPIO_Pin_14, GPIO_Pin_5,  GPIO_Pin_4};

// PWM GPIO Ports and Pins
GPIO_TypeDef* PwmGPIO[numMotors] = {GPIOC, GPIOD, GPIOB, GPIOB, GPIOB, GPIOA};
uint16_t pwm[numMotors] = {GPIO_Pin_6,  GPIO_Pin_15, GPIO_Pin_15,
                           GPIO_Pin_13, GPIO_Pin_1,  GPIO_Pin_7};

// TODO: Add timer array (of size 6) if multiple timers are used

// enum StatusLed { ERROR = 8, OK, HALT }stalusLed;

// enum DirectionEnum { STOP, FORWARD, RIGHT, BACKWARD, LEFT }Direction;
// Initialization Functions
void InitializeTimer();
void intializeWheels();

// Control motor by selecting
// wheelNumber as index, speed and direction
void controlWheel(const int index, const int speed, const int direct);

// Takes a direction from enum Direction
// to move all motors to a particular direction
void moveRover(int dir);

// Sets all dir and pwm to 0
// Required to start Cytron
void resetAll();

// Temporary for front left tire
void resetLeftFront();

int main() {
  InitializeTimer();
  intializeWheels();

  if (SysTick_Config(SystemCoreClock / 1000))
    while (1)
      ;

  // DEBUG CODE
  GPIO_InitTypeDef GPIO_InitStructure;
  // Enable Peripheral Clocks
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  // DEBUG CODE END

  // Motor roverMotor;
  // roverMotor.intializeWheels();

  // DEBUG CODE
  GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
  // DEBUG CODE END

  // roverMotor.resetAll();

  resetAll();
  Delay(1000);
  GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
  GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);

  // while(1) { Delay(1000); moveRover(FORWARD); Delay(1000); }
  while (1) {
    moveRover(FORWARD);
    Delay(100);
    moveRover(BACKWARD);
    Delay(100);
    moveRover(LEFT);
    Delay(100);
    moveRover(RIGHT);
    Delay(100);
  }
}

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime) {
  TimingDelay = nTime;
  while (TimingDelay != 0) {
    moveRover(currentState);
  }
}

void SysTick_Handler(void) {
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}

void InitializeTimer() {
  TIM_Cmd(TIM2, DISABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef timerInitStructure;
  timerInitStructure.TIM_Prescaler =
      65535 / 4;  // Divide reference clock to lower frequency
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // Counting
                                                            // Method098
  timerInitStructure.TIM_Period =
      17;  // Value to be loaded into auto-reload register to count from
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  timerInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timerInitStructure);
  TIM_Cmd(TIM2, ENABLE);
}

void intializeWheels() {
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

void controlWheel(const int index, const int speed, const int direct) {
  int timerValue = TIM_GetCounter(TIM2);
  // Speed control
  if (timerValue == 5 - speed)
    GPIO_WriteBit(PwmGPIO[index], pwm[index], Bit_SET);
  else if (timerValue == 5)
    GPIO_WriteBit(PwmGPIO[index], pwm[index], Bit_RESET);

  // Direction control
  if (direct)
    GPIO_WriteBit(DirGPIO[index], dir[index], Bit_SET);
  else
    GPIO_WriteBit(DirGPIO[index], dir[index], Bit_RESET);
}

void moveRover(int dir) {
  currentState = dir;
  switch (dir) {
    case STOP:
      controlWheel(0, 0, 0);
      controlWheel(1, 0, 0);
      controlWheel(2, 0, 0);
      controlWheel(3, 0, 0);
      controlWheel(4, 0, 0);
      controlWheel(5, 0, 0);
      break;
    case FORWARD:
      // Delay(10);
      controlWheel(0, 3, 1);
      controlWheel(1, 3, 1);
      controlWheel(2, 3, 1);
      controlWheel(3, 3, 1);
      controlWheel(4, 3, 1);
      controlWheel(5, 3, 1);
      break;
    case RIGHT:
      controlWheel(0, 3, 1);
      controlWheel(1, 3, 1);
      controlWheel(2, 3, 1);
      controlWheel(3, 3, 0);
      controlWheel(4, 3, 0);
      controlWheel(5, 3, 0);
      break;
    case BACKWARD:
      controlWheel(0, 3, 0);
      controlWheel(1, 3, 0);
      controlWheel(2, 3, 0);
      controlWheel(3, 3, 0);
      controlWheel(4, 3, 0);
      controlWheel(5, 3, 0);
      break;
    case LEFT:
      controlWheel(0, 3, 0);
      controlWheel(1, 3, 0);
      controlWheel(2, 3, 0);
      controlWheel(3, 3, 1);
      controlWheel(4, 3, 1);
      controlWheel(5, 3, 1);
      break;
    default:
      break;
  }
}

// It should set all dir and pwm to 0
void resetAll() {
  for (int i = 0; i < numMotors; i++) {
    GPIO_WriteBit(PwmGPIO[i], pwm[i], Bit_RESET);
    GPIO_WriteBit(DirGPIO[i], dir[i], Bit_RESET);
  }
}

void resetLeftFront() {
  GPIO_WriteBit(PwmGPIO[0], pwm[0], Bit_RESET);
  GPIO_WriteBit(DirGPIO[0], dir[0], Bit_RESET);
}