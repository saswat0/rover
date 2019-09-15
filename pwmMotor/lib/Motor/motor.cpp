#include <motor.h>

void Motor::InitializeTimer() {
	TIM_Cmd(TIM2, DISABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseInitTypeDef timerInitStructure;
  timerInitStructure.TIM_Prescaler = 65535/4;
  timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  timerInitStructure.TIM_Period = 17;
  timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  timerInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM2, &timerInitStructure);
  TIM_Cmd(TIM2, ENABLE);
}

void Motor::intializeWheels() {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);

  GPIO_InitTypeDef gpio;
  GPIO_StructInit(&gpio);
  gpio.GPIO_Mode = GPIO_Mode_OUT;
  gpio.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13 | GPIO_Pin_11;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &gpio);

  gpio.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOE, &gpio);
}


void Motor::controlWheel(const int index, const int speed, const int direct) {
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
    GPIO_WriteBit(DirGPIO[index],  dir[index], Bit_RESET);
}


void Motor::moveRover(const Direction dir) {
  switch (dir) {
    case 0:
      controlWheel(0, 0, 0);
      controlWheel(0, 0, 0);
      break;
    case 1:
      controlWheel(0, 3, 1);
      controlWheel(1, 3, 1);
      break;
    case 2:
      controlWheel(0, 3, 1);
      controlWheel(1, 3, 0);
      break;
    case 3:
      controlWheel(0, 3, 0);
      controlWheel(1, 3, 0);
      break;
    case 4:
      controlWheel(0, 3, 0);
      controlWheel(1, 3, 1);
      break;
    default:
      break;
  }
}

// It should set all dir and pwm to 0
void Motor::resetAll() {
	for(int i=0; i<numMotors; i++){
		GPIO_WriteBit(PwmGPIO[i], pwm[i], Bit_RESET);	
		GPIO_WriteBit(DirGPIO[i], dir[i], Bit_RESET);	
	}
}
