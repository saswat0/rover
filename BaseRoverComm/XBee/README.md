# Rover2k20_XBee
Scipts used to acheive communiation between pair of XBee S6B

### CLASSES :

XBee classes created to be called in other scripts.
Classes for both synchronous and asynchronous communcation.

##### Synchronous -
Each send calls the receive with a set timeout.

##### Asynchronous - 
Calling script has to identify corresponding received message for each.


### TESTING SCRIPTS : 

##### Bidirection - 
Contains scripts to acheive bidirectional communication between two xbees.
Simple send receive programs.

bidir1_xbee - Starts with receive inside loop.<br>
bidir2_xbee - Sends a packet before loop to start communication.<br>
Run bidir1_xbee first and then bidir2_xbee to avoid deadlock<br>

##### xbee_receive_serial
Script to receive data from other xbee using pyserial. When the xbee receives the data, it forwards it to the serial port. Use pyserial to read that data.

##### xbee_send_library
Script to send data to remote xbee using xbee library. The xbee broadcasts the message to the port mentioned. Port is hexadecimal in XCTU, but decimal in code.

Setting up xbees - https://xbplib.readthedocs.io/en/latest/getting_started_with_xbee_python_library.html#gsgconfigwifidevices<br>
Starting Program - <br>
https://xbplib.readthedocs.io/en/latest/getting_started_with_xbee_python_library.html#gsgappwifi
