CC=g++
CFLAGS=-Wall -std=c++14 -lncurses
SRCS=src/main.cpp src/level.cpp src/map.cpp src/room.cpp src/cell.cpp src/component.cpp src/entity.cpp src/system.cpp
EXE_NAME=alashack

build:
	$(CC) $(CFLAGS) $(SRCS) -o $(EXE_NAME)

clean:
	rm *.o
