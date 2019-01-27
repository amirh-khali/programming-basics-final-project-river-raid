BINARY = PLAY
OBJS = src/*.cpp

generator:
	g++ $(OBJS) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o $(BINARY)
	./PLAY
