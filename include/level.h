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
	
	void reset(void);
	void update(void);
	void load(std::string level_name);

	int levelnumber(void) const;

	int get_map_width(void) const;
	int get_map_height(void) const;
	const Cell& get_cell(int x, int y) const;

	bool is_walkable  (int x, int y)  const;
	bool is_explored  (int x, int y)  const;
	bool is_visible   (int x, int y)  const;
	bool is_in_bounds (int x, int y)  const;
	bool blocks_los   (int x, int y)  const;

	float get_cell_light(int x, int y) const;
	void set_cell_light(int x, int y, float value, bool force=false);

private:
	const int multipliers[4][8] = {
		{ 1, 0, 0, -1, -1, 0, 0, 1 },
		{ 0, 1, -1, 0, 0, -1, 1, 0 },
		{ 0, 1, 1, 0, 0, -1, -1, 0 },
		{ 1, 0, 0, 1, -1, 0, 0, -1 }
	};

	void fov(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy);

	static int _NEXT;

	int _level, _x, _y;
	const EntityManager& em;
	Map _map;

	friend class RenderSystem;
};

#endif
