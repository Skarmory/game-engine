#include "map.h"

Map::Map(void)
{
}

Map::Map(int x, int y) : _x_max(x), _y_max(y)
{
	_cells = std::vector<Cell*>(x * y);
}

Map::~Map(void)
{
	for(std::vector<Cell*>::iterator it = _cells.begin(); it != _cells.end(); it++)
	{
		delete *it;
	}
}

Cell& Map::get(int x, int y)
{
	return *_cells.at((y * _x_max) + x);
}

Cell& Map::get(int x, int y) const 
{
	return *_cells.at((y * _x_max) + x);
}

void Map::set(int x, int y, Cell* c)
{
	_cells[(y * _x_max) + x] = c;
}

int Map::width(void) const
{
	return _x_max;
}

int Map::height(void) const
{
	return _y_max;
}

bool Map::is_walkable(int x, int y)
{
	return get(x, y).is_walkable();
}

bool Map::is_explored(int x, int y)
{
	return get(x, y).explored;
}

bool Map::is_walkable(int x, int y) const
{
	return get(x, y).is_walkable();
}

bool Map::is_explored(int x, int y) const
{
	return get(x, y).explored;
}

void Map::set_explored(int x, int y, bool explored)
{
	get(x, y).explored = explored;
}

/*
void Map::set_light_intensity(int x, int y, float intensity)
{
	get(x, y).get_foreground_colour().setSaturation(intensity);
	get(x, y).get_background_colour().setSaturation(intensity);
}
*/
