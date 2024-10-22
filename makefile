CXX=        g++
CXXFLAGS=   -g -Wall -std=gnu++11
SHELL=      bash

all:		checkers

checkers:    checkers.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f checkers
