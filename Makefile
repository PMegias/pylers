CXX = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = 
INCLUDE = include
SRC = src

all: test build

test: main.cpp $(SRC)/SelectBox.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS) -I$(INCLUDE)

build: $(SRC)/*.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS) -I$(INCLUDE)


GAME.exe: main.cpp SelectBox.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS) -I$(INCLUDE)

clean:
	rm test build
