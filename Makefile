BINARY = PLAY
OBJS = src/*.cpp

generator:
	g++ $(OBJS) -o $(BINARY)
