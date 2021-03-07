FLAGS=-std=c++11 -pthread -O2
BIN_FOLDER=bin
SRC_FOLDER=src
INCLUDE=$(SRC_FOLDER)/options.hpp
COMPILER=clang++
LINK=-L./sparse1.6.0 -lsparselib1.6.0
LIB_INCLUDE=-I./sparse1.6.0/include

.PHONY: all main

all: \
	main

main: $(INCLUDE) $(SRC_FOLDER)/main.cpp
	$(COMPILER) $(SRC_FOLDER)/main.cpp $(FLAGS) $(LIB_INCLUDE) $(LINK) -o $(BIN_FOLDER)/spmv