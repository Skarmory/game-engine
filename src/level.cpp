#include "level.h"

#define MAX_SPACING_ATTEMPTS 1000

int Level::_NEXT = 0;

Level::Level(void) : _x(50), _y(50)
{
	_level = ++Level::_NEXT;
	_rooms = new std::vector<Room*>;

	genRooms();
}

Level::Level(int x, int y) : _x(x), _y(y)
{
	_level = ++Level::_NEXT;
	_rooms = new std::vector<Room*>;

	genRooms();
}

Level::~Level(void)
{
	for(std::vector<Room*>::iterator it = _rooms->begin();
		it != _rooms->end();
		it++)
	{
		delete *it;
	}
}

const int Level::getLevelNumber(void) const
{
	return _level; 
}

void Level::genRooms(void)
{
	int roomsCount = (rand() % 10) + 10;

	int x, y, w, h, attempts;

	for(int i = 0; i < roomsCount; i++)
	{
		attempts = 0;

		do {
			w = 5 + rand() % 5;
			h = 5 + rand() % 5;
			x = (rand() % (_x - w));
			y = (rand() % (_y - h));
			
			attempts++;
		} while(doesOverlap(x, y, w, h) && attempts<MAX_SPACING_ATTEMPTS);

		Room* r = new Room(x, y, w, h);
		_rooms->push_back(r);
	}
}

bool Level::doesOverlap(int x, int y, int w, int h) const
{
	for(std::vector<Room*>::const_iterator it = _rooms->begin();
		it != _rooms->end();
		it++)
	{
		const Dimensions d = (*it)->getDimensions();
		
		if(
			(((x >= d.x) && (x <= (d.x + d.width))) ||
			((d.x >= x) && (d.x <= (x + w)))) &&
			(((y >= d.y) && (y <= (d.y + d.height))) ||
			((d.y >= y) && (d.y <= (y + h))))
		)
		{
			return true;
		}
	}

	return false;
}
