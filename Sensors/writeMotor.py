from smbus2 import SMBus, i2c_msg
MOTOR_DEVICE_ADDRESS = 0x0d
I2C_MODE = 2

def parseMsg(msg):
	return [hex(i) for i in list(msg)]

bus = SMBus(I2C_MODE)

value=0

msg = i2c_msg.write(MOTOR_DEVICE_ADDRESS, [value])
bus.i2c_rdwr(msg)

