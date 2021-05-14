CXX = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS = 

all: GAME.exe

GAME.exe: main.cpp SelectBox.cpp
	$(CXX) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm *.exe