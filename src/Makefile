CC = g++
SFLAGS = -Wall -Wextra -Wpedantic -std=c++20
OFLAGS = -O3 -march=native -flto -DNDEBUG
LFLAGS = -lpthread
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = neuromancer

$(BIN): $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $@

$(OBJ): %.o: %.cpp
	$(CC) $(SFLAGS) $(OFLAGS) -c $<

clean:
	@rm -f $(OBJ) $(BIN)
