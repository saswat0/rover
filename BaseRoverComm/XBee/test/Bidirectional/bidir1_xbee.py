# Write using xbee library
# Read using serial

import serial
from time import sleep
from digi.xbee.devices import WiFiDevice

PORT = '/dev/ttyUSB0'
BAUD = 9600 

try:
    while True:
        # Part to receive data
        ser = serial.Serial(PORT,BAUD)
        print("Serial port initialized")
        data = ser.read_until(terminator=b'Z')
        print("Data read from port")
        ser.close()
        data = data[14:-1]
        print("Data Siced")
        data = data.decode()
        print("Data decoded")
        print(data)

        sleep(1)

        # Part to send data
        if data == 'Hello TCR2':
            print("Data Matched")
            device = WiFiDevice(PORT, BAUD)
            device.open()
            print("Xbee Initalized")
            device.send_ip_data_broadcast(9750, "Hello TCR1")
            print("Data sent")
            device.close()
            print('Xbee closed')
        sleep(1)
finally:
    device.close()
    ser.close()
