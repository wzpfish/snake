CXX=g++
CC=gcc
BIN=./bin
SRC=./src

CXXFLAGS=-g -std=c++11
THIRD_INCPATH=-I/usr/local/Cellar/glog/0.3.4/include -I/usr/local/Cellar/gflags/2.1.2/include
THIRD_LIB=-L/usr/local/Cellar/glog/0.3.4/lib -L/usr/local/Cellar/gflags/2.1.2/lib -lglog -lgflags -lcurses

.PHONY:clean

main.out:  $(SRC)/main.cc $(SRC)/frame.cc $(SRC)/snake.cc
	$(CXX) $(SRC)/main.cc $(SRC)/frame.cc $(SRC)/snake.cc  $(CXXFLAGS) $(THIRD_INCPATH) $(THIRD_LIB) -o $(BIN)/main

clean:
	rm -rf $(BIN)/*
