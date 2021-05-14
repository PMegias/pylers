CXX= g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS=

all: viz

viz: demo.cpp
	$(CXX) $(CFLAGS) demo.cpp -o GAME.exe $(LIBS)

clean:
	rm *.exe