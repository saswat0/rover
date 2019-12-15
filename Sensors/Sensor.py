from smbus2 import SMBus, i2c_msg

class Sensor:
	def __init__(self):
		self.SENSOR_DEVICE_ADDRESS = 0x0d
		self.SENSOR_BYTES = 20
		self.I2C_MODE = 2
		self.bus = SMBus(self.I2C_MODE)
		self.msg = i2c_msg.read(self.SENSOR_DEVICE_ADDRESS, self.SENSOR_BYTES)
		self.sensorIndex={'uv': [2], 'temp': [4, 5], 'pressure': [8, 9, 10, 11], 'atmtemp': [8, 9, 10, 11], 'hmidity': [8, 9, 10, 11]}
	def parseMsg(self, msg):
		return [hex(i) for i in list(msg)]

	def getAllSensorValue(self):
		self.bus.i2c_rdwr(self.msg)
		return parseMsg(self.msg)

	def getSensorValue(self, sensor):
		sensorValues = self.getAllSensorValue()
		bytesRequired = []
		for i in self.sensorIndex[sensor]:
			bytesRequired.append(sensorValues[i])
		return bytesRequired
