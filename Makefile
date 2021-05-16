CXX = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lgomp
CFLAGS = -O3 -fopenmp
INCLUDE = include
SRC = src

all: build

build: $(SRC)/*.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS) -I$(INCLUDE)

clean:
	rm build
