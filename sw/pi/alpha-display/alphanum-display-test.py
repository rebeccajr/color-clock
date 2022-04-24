#-------------------------------------------------------------------------------
# DESCRIPTION
# This file includes test code for the alpha numeric display backpack purchased
# from Adafruit. The data is sent over i2c serial.
#-------------------------------------------------------------------------------

import board
import busio
import time
from adafruit_ht16k33.segments import Seg14x4

from datetime import datetime

if __name__ == "__main__":

    i2c     = board.I2C()
    display = Seg14x4(i2c, address=0x70)

    the_current_time = datetime.now()
    str_time = the_current_time.strftime("%H%M")
    display.print(str_time)
