OBJS = main.cpp

OBJ_NAME = main

compile:
	g++ $(OBJS) -w -lSDL2 -o $(OBJ_NAME)
