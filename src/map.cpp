#include "map.h"

Map::Map(void)
{
}

Map::Map(int x, int y) : _width(x), _height(y)
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
	return *_cells.at((y * _width) + x);
}

const Cell& Map::get(int x, int y) const 
{
	return *_cells.at((y * _width) + x);
}

void Map::set(int x, int y, Cell* c)
{
	_cells[(y * _width) + x] = c;
}

bool Map::is_walkable(int x, int y) const
{
	return get(x, y)._walkable;
}

bool Map::is_explored(int x, int y) const
{
	return get(x, y)._explored;
}

void Map::set_explored(int x, int y, bool explored)
{
	get(x, y)._explored = explored;
}
