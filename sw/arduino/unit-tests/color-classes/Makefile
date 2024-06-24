#_____________________________________________________________________________
# PATHS
#_____________________________________________________________________________
SRC_DIR = /Users/rebeccarashkin/git/color-clock/sw/arduino/color-clock-driver
#HEADERS = $(SRC_DIR)/flux-clock.hpp
#HEADERS = flux-clock.hpp

#_____________________________________________________________________________
default: color-class-test

color-class-test.o: color-class-test.cpp $(SRC_DIR)/debug.hpp $(SRC_DIR)/hsv-color.hpp
	g++ -std=c++11 -c color-class-test.cpp -I$(SRC_DIR)

debug.o: $(SRC_DIR)/debug.cpp $(SRC_DIR)/debug.hpp
	g++ -std=c++11 -c $(SRC_DIR)/debug.cpp -I$(SRC_DIR)

color-classes.o: $(SRC_DIR)/color-classes.cpp $(SRC_DIR)/hsv-color.hpp
	g++ -std=c++11 -c $(SRC_DIR)/color-classes.cpp -I$(SRC_DIR)

color-class-test: color-class-test.o debug.o color-classes.o
	g++ -std=c++11 color-class-test.o debug.o color-classes.o -o color-class-test

clean:
	-rm -f *o
	-rm -f color-class-test