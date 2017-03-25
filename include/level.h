#ifndef level_h
#define level_h

#include "cell.h"
#include "map.h"


class Level
{
public:
	explicit Level(void);
	explicit Level(float depth);

	float get_map_width(void) const;
	float get_map_height(void) const;
	const Cell& get_cell(float x, float y) const;

	bool is_walkable  (float x, float y)  const;
	bool is_explored  (float x, float y)  const;
	bool is_in_bounds (float x, float y)  const;
	bool blocks_los   (float x, float y)  const;

private:
	float _depth;

	TerrainMap _base_map;

	friend class RenderSystem;
	friend class LightSystem;
	friend class VisibilitySystem;
	friend class LevelManager;
};

#endif
