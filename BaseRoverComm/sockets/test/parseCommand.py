
def parseCommand(bytes):
	prefix = 0xf00
	firstCommand = 0x0f0
	secondCommand = 0x00f

	x = int.from_bytes(bytes, byteorder='little', signed=False)

	baseFirstCommand = {
		0x040: 'Forward',
		0x050: 'Backward',
		0x060: 'Left',
		0x070: 'Right',
	}

	# check prefix for base motor
	if x&prefix == 0x000:
		print('Base Motor')
		
		if x&firstCommand==0x040:
			print('Forward')
		elif x&firstCommand==0x050:
			print('Backward')
		elif x&firstCommand==0x060:
			print('Left')
		elif x&firstCommand==0x070:
			print('Right')
		else:
			print('Stop')

	# check prefix for camera
	elif x&prefix == 0x100:
		print('Camera Control')
		if x&firstCommand == 0x000:
			print('Camera 1')
		elif x&firstCommand == 0x010:
			print('Camera 2')
		elif x&firstCommand == 0x020:
			print('Camera 3')
		elif x&firstCommand == 0x030:
			print('Camera 4')
		else:
			print("Invalid Camera")

	# check prefix for arm motor control
	elif x&prefix== 0x200:
		print("Base Arm Control")
		if x&firstCommand == 0x020:
			print("Motor Left")
		elif x&firstCommand == 0x030:
			print("Motor Right")    			
		else:
			print("Stop")

	# check prefix for actuator 1 control
	elif x&prefix== 0x300:
		print("Actuator 1 Control")
		if x&firstCommand == 0x020:
			print("Extend")
		elif x&firstCommand == 0x030:
			print("Retract")
		else:
			print("Stop")

	# check prefix for actuator 2 control
	elif x&prefix== 0x400:
		print("Actuator 2 Control")
		if x&firstCommand == 0x020:
			print("Extend")
		elif x&firstCommand == 0x030:
			print("Retract")
		else:
			print("Stop")
	
	# check prefix for actuator 3 control
	elif x&prefix== 0x500:
		print("Actuator 3 Control")
		if x&firstCommand == 0x020:
			print("Extend")
		elif x&firstCommand == 0x030:
			print("Retract")
		else:
			print("Stop")

	# check prefix for gripper rotation control
	elif x&prefix== 0x600:
		print("Gripper Rotate Control")
		if x&firstCommand == 0x020:
			print("Motor Left")
		elif x&firstCommand == 0x030:
			print("Motor Right")
		else:
			print("Stop")
	
	# check prefix for gripper claw 
	elif x&prefix== 0x700:
		print("Gripper Close Control")
		if x&firstCommand == 0x020:
			print("Open")
		elif x&firstCommand == 0x030:
			print("Close")
		else:
			print("Stop")
		
	# check prefix for soil sensor selection
	elif x&prefix== 0x800:
		print("Soil Sensor")
		if x&firstCommand == 0x080:
			print("Sensor 1")
		elif x&firstCommand == 0x040:
			print("Sensor 2")
		elif x&firstCommand == 0x020:
			print("Sensor 3")
		elif x&firstCommand == 0x010:
			print("Sensor 4")
		elif x&secondCommand == 0x08:
			print("Sensor 5")
		elif x&secondCommand == 0x04:
			print("Sensor 6")
		elif x&secondCommand == 0x02:
			print("Sensor 7")
		elif x&secondCommand == 0x01:
			print("Sensor 8")
		else:
			print("No change for soil sensor command")

	# check prefix for electrical sensor selection
	elif x&prefix== 0x900:
		print("Current/ Soil Sensor")
		if x&firstCommand == 0x080:
			print("Current Sensor 1")
		elif x&firstCommand == 0x040:
			print("Current Sensor 2")
		elif x&firstCommand == 0x020:
			print("Current Sensor 3")
		elif x&firstCommand == 0x010:
			print("Current Sensor 4")
		elif x&secondCommand == 0x08:
			print("Current Sensor 5")
		elif x&secondCommand == 0x04:
			print("Current Sensor 6")
		elif x&secondCommand == 0x02:
			print("Voltage Sensor 1")
		elif x&secondCommand == 0x01:
			print("Voltage Sensor 2")
		else:
			print("No change for electrical sensor command")

	# check prefix for getting GPS value
	elif x&prefix == 0xa00:
		print("Get GPS")
	elif x&prefix == 0xb00:
		print("Soil Setup")
		if x&firstCommand == 0x010:
			print("Auger up")
		elif x&firstCommand == 0x020:
			print("Auger down")
		elif x&firstCommand == 0x030:
			print("Soil Collect")
		else:
			print("No change for soil setup")

	# check prefix for autonomous 
	elif x&prefix == 0xc00:
		print("Autonomous Commands")
		if x&firstCommand == 0x000:
			print("Start")
		elif x&firstCommand == 0x010:
			print("Left")
		elif x&firstCommand == 0x020:
			print("Right")
		elif x&firstCommand == 0x020:
			print("Stop")
		else:
			print("No change for autonomous command")

	# check prefix for adding GPS lattitue 
	elif x&prefix == 0xd00:
		print("Add GPS Lat")

	# check prefix for adding GPS longitude
	elif x&prefix == 0xe00:
		print("Add GPS Long")

	# check prefix for RPM change 
	elif x&prefix == 0xf00:
		print("RPM Control")
		if x&firstCommand == 0x020:
			print("Increase RPM")
		elif x&firstCommand == 0x030:
			print("Decrease RPM")
		else:
			print("No change for RPM control")
	else:
		print("Invalid Prefix")


# print(parseBase('F').to_bytes(5, 'little'))
# parseCommand(0x320.to_bytes(3, 'little'))

import socket



sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
PORT = 8000
IP = '192.168.43.191'
data = bytes(1)

# print(data | 0x01)
# print('Sending Data ',data)
sock.bind(('',PORT))
sock.listen(5)
c,addr = sock.accept()
print('Got connection from', addr)

while True:
    data = c.recv(3)
    # print(data)
    if not data:
        break
    # print(hex(int.from_bytes(data,byteorder='little',signed=False)))
    # print(type(data))
    parseCommand(data)
