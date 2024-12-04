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
	@diff -y --suppress-common-lines <(./checkers < inputs/fullgame-1.txt) outputs/fullgame-1.txt > diff_output-1.txt || (echo "Gradescript 2 failed! Check diff_output-1.txt for details."; exit 1)
	@if [ ! -s diff_output-1.txt ]; then echo "Gradescript 2 passed!"; rm diff_output-1.txt; fi
	@diff -y --suppress-common-lines <(./checkers < inputs/fullgame-tom.txt) outputs/fullgame-tom.txt > diff_output-2.txt || (echo "Gradescript 3 failed! Check diff_output-2.txt for details."; exit 1)
	@if [ ! -s diff_output-1.txt ]; then echo "Gradescript 3 passed!"; rm diff_output-2.txt; fi
	@if [ -d "checkers.dSYM" ]; then \
	    rm -rf checkers.dSYM; \
	fi
	@echo "Testing done."	
