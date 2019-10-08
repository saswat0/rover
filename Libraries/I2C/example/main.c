#include <i2c.h>

/*
Code will Turn GPIO_E_8 high if i2c data is 0x01
Code will Turn GPIO_E_9 high if i2c data is 0x02
Code will Turn both if i2c data is 0x03
*/

void initLedPinAndClock();

int main() {
  // Setting LED Pins and clock
  initLedPinAndClock();

  I2C motorI2c;

  I2CInit(&motorI2c);

  while (1) {
		// Check if address is matched
    if (I2CAddressMatched(&motorI2c)) {

			// get data from i2c
      uint8_t data = I2CRecievedData(&motorI2c);

      if (data == 0x01) {
        GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);
      } else if (data == 0x02) {
        GPIO_WriteBit(GPIOE, GPIO_Pin_8, Bit_SET);
      } else if (data == 0x03) {
        GPIO_WriteBit(GPIOE, GPIO_Pin_8 | GPIO_Pin_9, Bit_RESET);
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
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}