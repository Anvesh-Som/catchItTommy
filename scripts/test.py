import serial
import time
arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=.1)
def write_read(x):
    x = 24+140
    arduino.write(bytes(x.encode('utf-8')))
    time.sleep(0.05)
#    data = arduino.readline()

while True:
    num = input("Enter a number: ") # Taking input from user
    write_read(str(num))
#    print(value) # printing the value
