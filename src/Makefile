CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20
CXXOPTFLAGS = -O3 -march=native -flto -DNDEBUG
LDLIBS = -lpthread

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = neuromancer

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) $(LDLIBS) -o $@

$(OBJ): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXXOPTFLAGS) -c $<

windows: CXX = x86_64-w64-mingw32-g++
windows: all

clean:
	@rm -f $(OBJ) $(BIN) $(BIN).exe
