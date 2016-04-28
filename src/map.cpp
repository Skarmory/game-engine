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
