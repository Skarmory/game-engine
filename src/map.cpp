#include "map.h"

Map::Map(void)
{
}

Map::Map(int x, int y) : _x_max(x), _y_max(y)
{
	_cells = std::vector<Cell*>(x * y);
}

Cell& Map::get(int x, int y) const 
{
	return *_cells.at((y * _y_max) + x);
}

void Map::set(int x, int y, Cell& c)
{
	_cells[(y * _y_max) + x] = &c;
}

int Map::width(void) const
{
	return _x_max;
}

int Map::height(void) const
{
	return _y_max;
}
