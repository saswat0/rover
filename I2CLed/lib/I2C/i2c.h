#ifndef __I2C_H
#define __I2C_H
#endif

#include<stm32f30x.h>
#include<stm32f30x_gpio.h>
#include<stm32f30x_rcc.h>
#include<stm32f30x_i2c.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct i2cStruct I2C;

struct i2cStruct{
	uint32_t ownAddress;
	I2C_TypeDef* i2cx;
	uint8_t nBytes;
	uint32_t timing;
};

void I2CInit(I2C* i2c);
FlagStatus I2CAddressMatched(I2C* i2c);
void I2CClearAddrFlag(I2C* i2c);
uint8_t I2CRecievedData(I2C* i2c);
