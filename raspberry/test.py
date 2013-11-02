
import serial
#types, struct, time

SERIAL_DEV='/dev/ttyAMA0'

serial = serial.Serial(SERIAL_DEV, 115200, timeout = 1)

CMD_LED_COLOR = 1
CMD_BRIGHTNESS = 2

def sendCmd(index, color):
    

for index in range(0, 32)
    serial.write()

