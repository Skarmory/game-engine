#include "room.h"

Room::Room(void)
{
}

Room::Room(int x, int y, int w, int h)
{
	Dimensions d;
	d.x = x;
	d.y = y;
	d.w = w;
	d.h = h;

	_dimensions = d;	
}

Room::Room(Dimensions& d)
{
	_dimensions = d;
}

Room::~Room(void)
{
}
