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
#include "cell.h"
#include "map.h"

class Level
{
public:
	Level(void);
	~Level(void);	
	
	void draw(void) const;
	void load(std::string level_name);

	int levelnumber(void) const;
	
private:
	static int _NEXT;

	int _level, _x, _y;
	Map _map;
};

#endif
