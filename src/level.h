#ifndef LEVEL_H
#define LEVEL_H

#include <ncurses.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include "room.h"

class Level
{
public:
	Level(void);
	Level(int x, int y);
	~Level(void);	
	
	std::vector<Room*>::const_iterator rooms_begin() const { return _rooms->begin(); }
	std::vector<Room*>::const_iterator rooms_end() const { return _rooms->end(); }

	const int getLevelNumber(void) const;

private:
	static int _NEXT;

	std::vector<Room*>* _rooms;
	int _level, _x, _y;

	void genRooms(void);
	bool doesOverlap(int x, int y, int w, int h) const;
};

#endif
