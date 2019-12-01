# read data received by xbee using pyserial 

import serial

PORT = '/dev/ttyUSB1'
BAUD = 9600

ser = serial.Serial(PORT)
ser.flushInput()
ser.flushOutput()
while True:
    data = ser.read_until(terminator=b'Z')
    # data = ser.read(21)
    # data = str(data)
    # data = data.decode()
    data = data[14:-1]
    data = data.decode()
    print(data)
