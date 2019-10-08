#include <i2c.h>
#include <motor.h>

/*
Code will Turn GPIO_E_8 high if i2c data is 0x01
Code will Turn GPIO_E_9 high if i2c data is 0x02
Code will Turn both if i2c data is 0x03
*/

void initLedPinAndClock();
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime);
void DelayMotor(Motor* motor, uint32_t nTime);

int main() {
  // Setting LED Pins and clock
  initLedPinAndClock();

  Motor motor;
  motorInit(&motor);
  InitializeTimer(&motor);
  IntializeWheels(&motor);

  I2C motorI2c;
  I2CInit(&motorI2c);

  if (SysTick_Config(SystemCoreClock / 1000))
    while (1)
      ;

  GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
  resetAll(&motor);
  Delay(1000);
  GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_RESET);
  GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);

  while (1) {
    // Check if address is matched
    if (I2CAddressMatched(&motorI2c)) {
      // get data from i2c
      uint8_t data = I2CRecievedData(&motorI2c);
      GPIO_WriteBit(GPIOE, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12, Bit_RESET);
      if (data == 0x01) {
        moveRover(&motor, FORWARD);
        GPIO_WriteBit(GPIOE, GPIO_Pin_9, Bit_SET);
      } else if (data == 0x02) {
        moveRover(&motor, BACKWARD);
        GPIO_WriteBit(GPIOE, GPIO_Pin_10, Bit_SET);
      } else if (data == 0x03) {
				moveRover(&motor, LEFT);
				GPIO_WriteBit(GPIOE, GPIO_Pin_11, Bit_SET);
      } else if (data == 0x04) {
				moveRover(&motor, RIGHT);
				GPIO_WriteBit(GPIOE, GPIO_Pin_12, Bit_SET);
      }
			else if (data == 0x05) {
				moveRover(&motor, STOP);
      }

        
      // Clear Address Flag
      // It should be called always at the end of if statement
      I2CClearAddrFlag(&motorI2c);
    }
  }
}

void initLedPinAndClock() {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin =
      GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
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