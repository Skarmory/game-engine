#include "room.h"

Room::Room(void)
{
}

Room::Room(int x, int y, int width, int height)
{
	Dimensions d;
	d.x = x;
	d.y = y;
	d.width = width;
	d.height = height;

	_dimensions = d;	
}

Room::Room(Dimensions& d)
{
	_dimensions = d;
}

Room::~Room(void)
{
}
