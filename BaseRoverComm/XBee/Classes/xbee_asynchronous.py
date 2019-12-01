'''
Xbee Class for asynchronous communication
'''
import time 
from digi.xbee.devices import WiFiDevice
import serial

class xbee_blocking:
    def __init__(self,port,read_timeout):
        '''
        PORT : Port to which xbee is connected
        BAUD : Baudrate of the serial connection
        receive_timeout : Time for which the read function will block
                          (in seconds)

        NOTE : DO NOT CHANGE THE BAUDRATE. XBEE'S BAUDRATE IS FIXED 
               AT 9600. 

        '''
        self.PORT = port
        self.BAUD = 9600
        self.receive_timeout = read_timeout

    def receive_data(self,return_length):
        '''
        return_length : Expected length of the return message

        NOTES : 
        
        1. return_length should be predetermined for every command
        2. Calling script will have to time the gap between send and receive.
        '''
        ser = serial.Serial(port=self.PORT,baudrate=self.BAUD,timeout=self.receive_timeout)
        data = ser.read(len+14)
        ser.close()
        data = data[14:-1]
        data = data.decode()
        return data

    def send_data(self,xbee_port,command,return_length):
        '''
        xbee_port : Socket port of xbee used
        command : command to be sent to rover
        return_length : Expected length of return message

        NOTE : This function will send the command and close.
               Calling script has to put gap between 
        '''
        device = WiFiDevice(port=self.PORT,baud_rate=self.BAUD)
        device.open()
        device.send_ip_data_broadcast(xbee_port,command)
        device.close()

        
