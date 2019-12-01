# write data to remote xbee using xbee library

PORT = '/dev/ttyUSB0'
BAUD = 9600

from time import sleep
from digi.xbee.devices import WiFiDevice
device = WiFiDevice(PORT,BAUD)
device.open()

try:
    while True:
        device.send_ip_data_broadcast(9750, "Hello TCR2")
        print("Data Sent : Hello TCR2")
        sleep(1)
finally:
    device.close()
