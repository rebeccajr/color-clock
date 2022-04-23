#-------------------------------------------------------------------------------
# DESCRIPTION
# This file includes test code for the alpha numeric display backpack purchased
# frm Adafruit. The data is sent over i2c serial.
#-------------------------------------------------------------------------------

import board
import busio
from adafruit_ht16k33.segments import Seg14x4




if __name__ == "__main__":

    # try to create an i2c device
    #i2c = busio.I2C(board.SCL, board.SDA)
    #print('I2C ok!')


    i2c = board.I2C()
    display = Seg14x4(i2c, address=0x70)
    display.print_hex(0x1A2B)
    display.print("gabe")

