CXX=        g++
CXXFLAGS=   -g -Wall -std=gnu++11
SHELL=      bash

SRC=checkers.cpp
BIN=checkers

.PHONY:	all clean format test

all:    $(BIN)

$(BIN):    $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(BIN)
format:
	clang-format -i $(SRC)
test:	all
	@echo "Testing output!"
	@diff -y --suppress-common-lines <(./checkers < inputs/fullgame.txt) outputs/fullgame.txt > diff_output.txt || (echo "Gradescript 1 failed! Check diff_output.txt for details."; exit 1)
	@if [ ! -s diff_output.txt ]; then echo "Gradescript 1 passed!"; rm diff_output.txt; fi
	@echo "Testing done."
	
