#include <motor.h>
#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <stm32f30x_tim.h>

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime);
void DelayMotor(Motor* motor, uint32_t nTime);

int main() {
  Motor motor;
  motorInit(&motor);

  if (SysTick_Config(SystemCoreClock / 1000))
    while (1)
      ;


  resetAll(&motor);
  Delay(1000);
  GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
  GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);

  while (1) {
    moveRover(&motor, FORWARD);
    DelayMotor(&motor, 2000);

    moveRover(&motor, BACKWARD);
    DelayMotor(&motor, 2000);

    moveRover(&motor, LEFT);
    DelayMotor(&motor, 2000);

    moveRover(&motor, RIGHT);
    DelayMotor(&motor, 2000);
    
    moveRover(&motor, STOP);
    Delay(2000);

  }
}

void Delay(uint32_t nTime) {
  TimingDelay = nTime;
  while (TimingDelay != 0) {
    ;
  }
}

void SysTick_Handler(void) {
  if (TimingDelay != 0x00) {
    TimingDelay--;
  }
}

void DelayMotor(Motor* motor, uint32_t nTime) {
  TimingDelay = nTime;
  while (TimingDelay != 0) {
    moveRover(motor, motor->currentState);
  }
}