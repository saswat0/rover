def parseBase(direction):
    x = 0x000
    if direction == 'F':
      x|=0x40
    elif direction == 'B':
      x|=0x50
    elif direction == 'L':
      x|=0x60
    elif direction == 'R':
      x|=0x70
    # elif direction == 'S':
    #     x|=000
    return x

def parseCamera(cameraNum):
    x = 0x100
    if cameraNum == 1:
        x|=0x00
    if cameraNum == 2:
        x|=0x10
    if cameraNum == 3:
        x|=0x20
    if cameraNum == 4:
        x|=0x30
    return x

def parseArm(direction):
    x = 0x200
    if direction=='L':
        x|=0x020
    if direction=='R':
        x|=0x030
    return x

def parseActuator1(state):
    x = 0x300
    if state=='E':
        x|=0x20
    if state=='R':
        x|=0x30
    return x

def parseActuator2(state):
    x = 0x400
    if state=='E':
        x|=0x20
    if state=='R':
        x|=0x30
    return x

def parseActuator3(state):
    x = 0x500
    if state=='E':
        x|=0x20
    if state=='R':
        x|=0x30
    return x

def parseGripperDir(direction):
    x = 0x600
    if direction=='L':
        x|=0x20
    if direction=='R':
        x|=0x30
    return x

def parseGripperState(state):
    x = 0x700
    if state=='O':
        x|=0x20
    if state=='C':
        x|=0x30
    return x

def parseSoil(sensorNum):
    x = 0x800
    if sensorNum==1:
        x|=0x80
    if sensorNum==2:
        x|=0x40
    if sensorNum==3:
        x|=0x20
    if sensorNum==4:
        x|=0x10
    if sensorNum==5:
        x|=0x8
    if sensorNum==6:
        x|=0x4
    if sensorNum==7:
        x|=0x2
    if sensorNum==8:
        x|=0x1
    return x

def parseElectrical(sensorNum):
    x = 0x900
    if sensorNum==1:
        x|=0x80
    if sensorNum==2:
        x|=0x40
    if sensorNum==3:
        x|=0x20
    if sensorNum==4:
        x|=0x10
    if sensorNum==5:
        x|=0x8
    if sensorNum==6:
        x|=0x4
    if sensorNum==7:
        x|=0x2
    if sensorNum==8:
        x|=0x1
    return x

def parseGpsRequest():
    x = 0xa00
    return x

def parseSoilSetup(step):
    x = 0xb00
    if step=='augerUp':
        x|=0x10
    if step=='augerDown':
        x|=0x20
    if step=='soilCollect':
        x|=0x30
    return x 

def parseAutonomousCommands(command):
    x = 0xc00
    if command=='startAutonomous':
        x|=0x00
    if command=='goLeft':
        x|=0x10
    if command=='goRight':
        x|=0x20
    if command=='stop':
        x|=0x30
    return x 

def parseAddLatitude(lattitude):
    x= 0xd00
    # attach latitude to end of prefix
    return x


def parseAddLongitude(longitude):
    x= 0xe00
    # attach longitude to end of prefix
    # print(type(x))
    return x

def parsePWM(state):
    x = 0xf00
    if state == 'U':
        x|=0x020
    if state == 'D':
        x|=0x030
    return x

import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
PORT = 8000
IP = '192.168.43.191'

sock.connect((IP,PORT))

sock.send(parseBase('F').to_bytes(3,'little'))
sock.send(parseCamera(1).to_bytes(3,'little'))
sock.send(parseArm('L').to_bytes(3,'little'))
sock.send(parseActuator1('E').to_bytes(3,'little'))
sock.send(parseActuator2('R').to_bytes(3,'little'))
sock.send(parseActuator3('E').to_bytes(3,'little'))
sock.send(parseGripperDir('L').to_bytes(3,'little'))
sock.send(parseGripperState('O').to_bytes(3,'little'))
sock.send(parseSoil(3).to_bytes(3,'little'))
sock.send(parseElectrical(5).to_bytes(3,'little'))
sock.send(parseElectrical(8).to_bytes(3,'little'))
sock.send(parseGpsRequest().to_bytes(3,'little'))
sock.send(parseSoilSetup('augerDown').to_bytes(3,'little'))
sock.send(parseAutonomousCommands('startAutonomous').to_bytes(3,'little'))
sock.send(parseAddLatitude('lattiude').to_bytes(3,'little'))
sock.send(parseAddLongitude('longitude').to_bytes(3,'little'))
sock.send(parsePWM('U').to_bytes(3,'little'))

sock.close()
