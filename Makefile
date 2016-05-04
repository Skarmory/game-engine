CC=g++
CFLAGS=-Wall -std=c++0x -lncurses
GAME=incarnate

SRCS=$(wildcard src/*.cpp)
INCL=$(wildcard include/*.h)
OBJS=$(patsubst src/%.cpp,build/%.o,$(SRCS))

.PHONY: all clean default
default: $(GAME)
all: default

build/%.o: src/%.cpp $(INCL)
	$(CC) $(CFLAGS) -I include -c $< -o $@ 

$(GAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(GAME) -ltinfo

clean:
	rm build/*.o; rm $(GAME)
