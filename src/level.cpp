#include "level.h"

#include "light.h"

Level::Level(void) : _depth(-1)
{}

Level::Level(float depth) : _depth(depth)
{}

bool Level::is_walkable(float x, float y) const
{
	return _base_map.is_walkable(x, y);
}

bool Level::is_explored(float x, float y) const
{
	return _base_map.is_explored(x, y);
}

bool Level::is_in_bounds(float x, float y) const
{
	return (x >= 0 && x < _base_map.width() && y >= 0 && y < _base_map.height());
}

bool Level::blocks_los(float x, float y) const
{
	return _base_map.get(x, y)->is_los_blocker();
}

float Level::get_map_width(void) const
{
	return _base_map.width();
}

float Level::get_map_height(void) const
{
	return _base_map.height();
}

const Cell& Level::get_cell(float x, float y) const
{
	return *_base_map.get(x, y);
}