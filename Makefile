CC=g++
CFLAGS=-Wall -std=c++0x -lncurses
SRCS=src/main.cpp src/level.cpp src/map.cpp src/cell.cpp src/entity.cpp src/component.cpp src/graphic_component.cpp src/location_component.cpp src/system.cpp src/render_system.cpp
EXE_NAME=alashack

build:
	$(CC) $(CFLAGS) $(SRCS) -o $(EXE_NAME)

clean:
	rm *.o
