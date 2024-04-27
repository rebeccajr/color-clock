#_____________________________________________________________________________
# PATHS
#_____________________________________________________________________________
#SRC_DIR = /mnt/c/Users/rebec/git/color-clock/sw/arduino/color-clock-driver
SRC_DIR = /Users/rebeccarashkin/git/color-clock/sw/arduino/color-clock-driver
HEADERS = $(SRC_DIR)/flux-clock.hpp
#HEADERS = flux-clock.hpp

#_____________________________________________________________________________
default: ctime-test

ctime-test.o: ctime-test.cpp $(SRC_DIR)/flux-clock.hpp
	g++ -c ctime-test.cpp -I$(SRC_DIR)

flux-clock.o: $(SRC_DIR)/flux-clock.cpp $(SRC_DIR)/flux-clock.hpp
	g++ -c $(SRC_DIR)/flux-clock.cpp -I$(SRC_DIR)

ctime-test: ctime-test.o flux-clock.o
	g++ ctime-test.o flux-clock.o -o ctime-test

clean:
	-rm -f *o
	-rm -f ctime-test