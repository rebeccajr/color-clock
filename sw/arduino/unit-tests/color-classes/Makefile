#_______________________________________________________________________
#       _   __   _   _ _   _   _   _         _
#  |   |_| | _  | | | V | | | | / |_/ |_| | /
#  |__ | | |__| |_| |   | |_| | \ |   | | | \_
#   _  _         _ ___  _       _ ___   _                        / /
#  /  | | |\ |  \   |  | / | | /   |   \                        (**)
#  \_ |_| | \| _/   |  | \ |_| \_  |  _/                        (____)o
#_______________________________________________________________________
# PATHS
#_____________________________________________________________________________
# Path on Ubuntu
SRC_DIR = /home/flux/git/color-clock/sw/arduino/color-clock-driver

#_____________________________________________________________________________
#_____________________________________________________________________________
default: color-class-test

#_______________________________________________________________________
# This works
#_______________________________________________________________________

# Note: order of .o arguments doesn't matter

debug.o: $(SRC_DIR)/rgb-color.hpp $(SRC_DIR)/hsv-color.hpp $(SRC_DIR)/debug.hpp $(SRC_DIR)/debug.cpp
	g++ -std=c++11 -c -I$(SRC_DIR) $(SRC_DIR)/debug.cpp

rgb-color.o: $(SRC_DIR)/rgb-color.hpp $(SRC_DIR)/rgb-color.cpp
	g++ -std=c++11 -c -I$(SRC_DIR) $(SRC_DIR)/rgb-color.cpp

hsv-color.o: $(SRC_DIR)/rgb-color.hpp $(SRC_DIR)/hsv-color.hpp  $(SRC_DIR)/hsv-color.cpp
	g++ -std=c++11 -c -I$(SRC_DIR) $(SRC_DIR)/hsv-color.cpp

color-class-test.o: color-class-test.cpp $(SRC_DIR)/debug.hpp $(SRC_DIR)/hsv-color.hpp $(SRC_DIR)/rgb-color.hpp
	g++ -std=c++11 -c color-class-test.cpp -I$(SRC_DIR)

color-class-test: color-class-test.o debug.o rgb-color.o hsv-color.o
	g++ -std=c++11 debug.o rgb-color.o hsv-color.o color-class-test.o -o color-class-test
#_______________________________________________________________________


#_______________________________________________________________________
# This works
#_______________________________________________________________________
#debug.o: $(SRC_DIR)/debug.hpp $(SRC_DIR)/debug.cpp
#	g++ -std=c++11 -c -I$(SRC_DIR) $(SRC_DIR)/debug.cpp
#
#color-class-test.o: color-class-test.cpp $(SRC_DIR)/debug.hpp
#	g++ -std=c++11 -c color-class-test.cpp -I$(SRC_DIR)
#
#color-class-test: debug.o color-class-test.o
#	g++ -std=c++11 debug.o color-class-test.o -o color-class-test
#_______________________________________________________________________

clean:
	-rm -f *o
	-rm -f color-class-test