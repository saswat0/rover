#include "i2c.h"

void I2CInit(I2C* i2c) {
  i2c->ownAddress = 0x1A;
  i2c->i2cx = I2C2;
  i2c->nBytes = 1;
  i2c->timing = 0x0000020B;

  // Alternate timing value: 0x00130309;

  // Enable I2C Clock
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  // Initialize GPIO
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Configure Alternate Function for GPIO
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_4);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_4);

  // Initialize I2C
  I2C_InitTypeDef I2C_InitStructure;
  I2C_StructInit(&I2C_InitStructure);

  I2C_DeInit(I2C2);
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;

  I2C_InitStructure.I2C_Timing = i2c->timing;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_OwnAddress1 = i2c->ownAddress;
  I2C_InitStructure.I2C_DigitalFilter = 0x00;
  I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
  I2C_StretchClockCmd(I2C2, DISABLE);
  I2C_GenerateSTOP(I2C2, ENABLE);
  I2C_NumberOfBytesConfig(I2C2, i2c->nBytes);

  I2C_Init(I2C2, &I2C_InitStructure);
  I2C_Cmd(I2C2, ENABLE);
}

FlagStatus I2CAddressMatched(I2C* i2c) {
  return I2C_GetFlagStatus(i2c->i2cx, I2C_FLAG_ADDR);
}

void I2CClearAddrFlag(I2C* i2c) {
  I2C_ClearFlag(i2c->i2cx, I2C_ICR_ADDRCF);
  while (I2C_GetFlagStatus(i2c->i2cx, I2C_FLAG_ADDR) == SET)
    ;
}

uint8_t I2CRecievedData(I2C* i2c) { return I2C_ReceiveData(i2c->i2cx); }