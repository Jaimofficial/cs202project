CXX=        g++
CXXFLAGS=   -g -Wall -std=gnu++11
SHELL=      bash

SRC=checkers.cpp
BIN=checkers

.PHONY:	all clean format

all:    $(BIN)

$(BIN):    $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(BIN)
format:
	clang-format -i $(SRC)

