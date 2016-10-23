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
	
	void base_draw(void);
	void draw(void);
	void load(std::string level_name);

	int levelnumber(void) const;

	bool is_walkable(int, int) const;
	bool is_walkable(int, int);

	bool is_explored(int, int) const;
	bool is_explored(int, int);

	void set_explored(int, int, bool);

	bool is_in_bounds(int, int) const;

	bool blocks_los(int, int) const;
	
	void set_cell_light(int x, int y, float value, float saturation, bool force=false);

private:
	static int _NEXT;

	int _level, _x, _y;
	Map _map;
};

#endif
