CC = c++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin

EXP_OBJ = $(OBJ)/Expression.o $(OBJ)/main.o
EXP_INC = $(INC)/Expression.hpp
STACK_INC = $(INC)/Stack.hpp
NODE_INC = $(INC)/Node.hpp
CFLAGS = -Wall -c -I$(INC)

EXE = $(BIN)/main

run: $(EXE)
		$(EXE) < input.txt
	
$(BIN)/main: $(EXP_OBJ)
	$(CC) -pg -o $(BIN)/main $(EXP_OBJ) $(LIBS)

$(OBJ)/Expression.o: $(EXP_INC) $(STACK_INC) $(NODE_INC) $(SRC)/Expression.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Expression.o $(SRC)/Expression.cpp

$(OBJ)/main.o: $(EXP_INC) $(PILHA_INC) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

clean:
		rm -f $(EXE) $(EXP_OBJ)
		clear
