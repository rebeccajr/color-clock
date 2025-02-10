
#_______________________________________________________________________
#_______________________________________________________________________
#       _   __   _   _ _   _   _   _         _
#  |   |_| | _  | | | V | | | | / |_/ |_| | /
#  |__ | | |__| |_| |   | |_| | \ |   | | | \_
#   _  _         _ ___  _       _ ___   _                        / /
#  /  | | |\ |  \   |  | / | | /   |   \                        (^^)
#  \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
#_______________________________________________________________________
#_______________________________________________________________________
#
#-----------------------------------------------------------------------
#  Copyright 2024, Rebecca Rashkin
#  -------------------------------
#  This code may be copied, redistributed, transformed, or built upon in
#  any format for educational, non-commercial purposes.
#
#  Please give me appropriate credit should you choose to use this
#  resource. Thank you :)
#-----------------------------------------------------------------------
#
#_______________________________________________________________________
#  //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\   //\^.^/\\
#_______________________________________________________________________

#_______________________________________________________________________
# DESCRIPTION
# Script to define DEBUG_CPP in the macros for ColorClock
#_______________________________________________________________________

from os import getcwd, path


MACROS_FILE_PATH: str = path.join('..'
  , '..'
  ,'arduino'
  , 'color-clock-driver'
  , 'flux-macros.hpp'
  )

if __name__ == '__main__':

  this_script_path = path.dirname(
    path.abspath(__file__)
    )

  macros_file: str = path.join(this_script_path, MACROS_FILE_PATH)
  macros: str

  # Read in macros
  with open(macros_file, 'r') as f:

    macros = f.read()

    # Uncomment build flags
    macros = macros.replace('// #define DEBUG_CPP', '#define DEBUG_CPP')
    macros = macros.replace('//#define DEBUG_CPP' , '#define DEBUG_CPP')

  with open(macros_file, 'w') as f:
    f.write(macros)
