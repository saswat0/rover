'''
Xbee Class for synchronous communication
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
        2. DO NOT CALL THIS FUNCTION SEPARATELY. 
           In synchronous communication every send has an equivalent 
           receive. Send function will call the receive function.
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

        NOTE : This function will send the command, open the serial 
               port and wait for receive_timeout seconds for a reply
               from rover. It will receive the data and return it to 
               calling script
        '''
        device = WiFiDevice(port=self.PORT,baud_rate=self.BAUD)
        device.open()
        device.send_ip_data_broadcast(xbee_port,command)
        device.close()

        return_data = self.receive_data(return_length)
        return return_data
