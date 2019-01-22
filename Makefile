BINARY = PLAY
OBJS = src/*.cpp

generator:
	g++ $(OBJS) -lSDL2 -o $(BINARY)
	./PLAY
