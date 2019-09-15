#include <motor.h>

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime) {
  TimingDelay = nTime;
  while (TimingDelay != 0)
    ;
}

void SysTick_Handler(void) {
  if (TimingDelay != 0x00) TimingDelay--;
}

int main() {

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

  if (SysTick_Config(SystemCoreClock / 1000))
    while (1)
      ;

	Motor roverMotor;

	// DEBUG CODE
  GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
	// DEBUG CODE END

	roverMotor.resetAll();
  Delay(1000);
  GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
  GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);

  while(1) roverMotor.moveRover(roverMotor.FORWARD);
}
