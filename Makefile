BINARY = PLAY
OBJS = src/*.cpp

generator:
	g++ $(OBJS) -lSDL2 -lSDL2_image -o $(BINARY)
	./PLAY
