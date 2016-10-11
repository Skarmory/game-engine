#ifndef level_h
#define level_h

#include <stdlib.h>
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
#include <assert.h>

#include "libtcod.hpp"
#include "cell.h"
#include "map.h"

class Level
{
public:
	Level(void);
	~Level(void);	
	
	void draw(void);
	void load(std::string level_name);

	int levelnumber(void) const;

	bool is_walkable(int, int) const;
	bool is_walkable(int, int);

	bool is_explored(int, int) const;
	bool is_explored(int, int);

	bool is_in_bounds(int, int) const;
	
	void set_explored(int, int, bool);
	void set_light_intensity(int, int, float);

	void set_cell_light(int x, int y, float value);

private:
	static int _NEXT;

	int _level, _x, _y;
	Map _map;
};

#endif
