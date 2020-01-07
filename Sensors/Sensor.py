from smbus2 import SMBus, i2c_msg

class Sensor:
	def __init__(self):
		self.SENSOR_DEVICE_ADDRESS = 0x0d
		self.SENSOR_BYTES = 20
		self.I2C_MODE = 1
		self.bus = SMBus(self.I2C_MODE)
		self.msg = i2c_msg.read(self.SENSOR_DEVICE_ADDRESS, self.SENSOR_BYTES)
		self.sensorIndex={'uv': [2], 'temp': [4, 5], 'pressure': [8, 9, 10, 11], 'atmtemp': [8, 9, 10, 11], 'humidity': [8, 9, 10, 11]}
	def parseMsg(self, msg):
		return [hex(i) for i in list(msg)]

	def getAllSensorValue(self):
		msg = self.msg
		self.bus.i2c_rdwr(msg)
		return self.parseMsg(msg)

	def getSensorValue(self, sensor):
		sensorValues = self.getAllSensorValue()
		bytesRequired = []
		for i in self.sensorIndex[sensor]:
			bytesRequired.append(sensorValues[i])
		return bytesRequired

	def getSensorValueBytes(self):
		msg = self.msg
		self.bus.i2c_rdwr(msg)
		return msg.__bytes__()	

	def close(self):
		self.bus.close()
