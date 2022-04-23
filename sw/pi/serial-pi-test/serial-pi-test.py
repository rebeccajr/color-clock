'''
DESCRIPTION
This file contains test code for the serial interfaces on a Raspberry Pi.
'''

import board
import digitalio
import busio

print('Hello blinka!')

# try to create a Digital input
pin = digitalio.DigitalInOut(board.D4)

# try to create an i2c device
i2c = busio.I2C(board.SCL, board.SDA)
print('I2C ok!')

# try to create an spi device
spi= busio.SPI(board.SCLK, board.MOSI, board.MISO)
print('SPI ok!')

print('all done!')
