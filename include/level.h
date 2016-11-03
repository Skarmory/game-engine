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

private:
	static int _NEXT;

	int _level, _x, _y;
	const EntityManager& em;

	TerrainMap _base_map;
	Map<float> _light_map;
	Map<short> _vision_map;

	friend class RenderSystem;
	friend class LightSystem;
	friend class VisibilitySystem;
};

#endif
