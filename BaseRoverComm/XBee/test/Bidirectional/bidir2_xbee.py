#  bidirectional script with sending test data first

import serial
from time import sleep
from digi.xbee.devices import WiFiDevice

PORT = '/dev/ttyUSB0'
BAUD = 9600 

device = WiFiDevice(PORT, BAUD)
print('XBee Device Initialized')
device.open()
print('XBee Device Opened')
device.send_ip_data_broadcast(9750, "Hello TCR2")
print('Initial Packet Sent')
device.close()
print('Device Closed')

sleep(1)

try:
    while True:
        ser = serial.Serial(PORT,BAUD)
        print('Serial Port Initialized')
        # data = ser.read_until(terminator=b'TCR1 ')
        data = ser.read(25)
        print('Data Read')
        ser.close()
        print('Serial Port Closed')
        data = data[14:-1]
        data = data.decode()
        print('Data received is: ',data)
        
        sleep(1)
        
        # if data == 'Hello TCR1':
        device = WiFiDevice(PORT, BAUD)
        print('XBee Device Initialized')
        device.open()
        print('XBee Device Opened')
        device.send_ip_data_broadcast(9750, "Hello TCR2")
        print('Data Sent')
        device.close()
        print('XBee Closed')
        sleep(1)
finally:
    device.close()
    ser.close()
    
