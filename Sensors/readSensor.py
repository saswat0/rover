from Sensor import Sensor
from smbus2 import SMBus, i2c_msg

roverSensor = Sensor()

print(roverSensor.getAllSensorValue())