#ifndef level_h
#define level_h

#include <ncurses.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <assert.h>
#include "room.h"
#include "cell.h"
#include "map.h"

class Level
{
public:
	Level(void);
	~Level(void);	
	
	//std::vector<Room*>::const_iterator rooms_begin() const { return _rooms.begin(); }
	//std::vector<Room*>::const_iterator rooms_end() const { return _rooms.end(); }

	void init(void);
	void draw(void) const;
	void load(std::string level_name);

	int levelnumber(void) const;
	
private:
	static int _NEXT;

	std::vector<Room*> _rooms;
	int _level, _x, _y;
	Map _map;


	void mkrooms(void);
	void mkcorridors(void);
	bool overlaps(int x, int y, int w, int h) const;
};

#endif
