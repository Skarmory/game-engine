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
#include "entity_manager.h"
#include "cell.h"
#include "map.h"
#include "light.h"

class Level
{
public:
	Level(const EntityManager& em);
	~Level(void);	
	
	void base_draw(void);
	void draw(void);
	void load(std::string level_name);

	int levelnumber(void) const;

	bool is_walkable(int, int) const;

	bool is_explored(int, int) const;

	bool is_visible(int, int) const;

	float get_cell_light(int, int);

	bool is_in_bounds(int, int) const;

	bool blocks_los(int, int) const;
	
	void set_cell_light(int x, int y, float value, float saturation, bool force=false);

private:
	const int multipliers[4][8] = {
		{ 1, 0, 0, -1, -1, 0, 0, 1 },
		{ 0, 1, -1, 0, 0, -1, 1, 0 },
		{ 0, 1, 1, 0, 0, -1, -1, 0 },
		{ 1, 0, 0, 1, -1, 0, 0, -1 }
	};

	void fov(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy);
	void set_explored(int, int, bool);

	static int _NEXT;

	int _level, _x, _y;
	const EntityManager& em;
	Map _map;
};

#endif
