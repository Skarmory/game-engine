#include "level.h"

Level::Level(void) : _depth(-1)
{}

Level::Level(int depth) : _depth(depth)
{}

bool Level::is_walkable(int x, int y) const
{
	return _base_map.is_walkable(x, y);
}

bool Level::is_explored(int x, int y) const
{
	return _base_map.is_explored(x, y);
}

bool Level::is_in_bounds(int x, int y) const
{
	return (x >= 0 && x < _base_map.width() && y >= 0 && y < _base_map.height());
}

bool Level::blocks_los(int x, int y) const
{
	return _base_map.get(x, y)->is_los_blocker();
}

int Level::get_map_width(void) const
{
	return _base_map.width();
}

int Level::get_map_height(void) const
{
	return _base_map.height();
}

const Cell& Level::get_cell(int x, int y) const
{
	return *_base_map.get(x, y);
}