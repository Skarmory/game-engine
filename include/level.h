#ifndef level_h
#define level_h

#include "cell.h"
#include "map.h"
#include "light.h"

class Level
{
public:
	explicit Level(void);
	explicit Level(int depth);

	int get_map_width(void) const;
	int get_map_height(void) const;
	const Cell& get_cell(int x, int y) const;

	bool is_walkable  (int x, int y)  const;
	bool is_explored  (int x, int y)  const;
	bool is_in_bounds (int x, int y)  const;
	bool blocks_los   (int x, int y)  const;

private:
	int _depth;

	TerrainMap _base_map;

	friend class RenderSystem;
	friend class LightSystem;
	friend class VisibilitySystem;
	friend class LevelManager;
};

#endif
