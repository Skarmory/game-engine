#include "map.h"


bool TerrainMap::is_walkable(int x, int y) const
{
	return Map<Cell*>::get(x, y)->is_walkable();
}

bool TerrainMap::is_explored(int x, int y) const
{
	return Map<Cell*>::get(x, y)->is_explored();
}

