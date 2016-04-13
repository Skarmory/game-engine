#include "level.h"

#define MAX_SPACING_ATTEMPTS 1000

int Level::_NEXT = 0;

Level::Level(void)
{
	_level = ++Level::_NEXT;
	//_rooms = new std::vector<Room*>;
}

Level::~Level(void)
{
	//for(std::vector<Room*>::iterator it = _rooms->begin(); it != _rooms->end(); it++)
	//	delete *it;

	//for(int i = 0; i < _x; i++)
	//	delete[] _map[i];

	//delete[] _map;
	//delete _rooms;
}

int Level::levelnumber(void) const
{
	return _level;
}

void Level::load(std::string level_name)
{
	std::stringstream sstream;
	std::string path;
	std::string line;
	std::ifstream file;
	std::string delimiter = "=";
	std::string option;
	std::string value;

	sstream << "levels" << "/" << level_name << ".dat";
    path = sstream.str();	

	file.open(path);
	assert(file.is_open());

	while(getline(file, line))
	{		
		if(line == "MAP DATA") 
		{
			int y = 0;
			while(getline(file, line))
			{
				if(line == "END MAP DATA")
					break;
				
				for(int x = 0; x < _map.width(); x++)
				{
					Cell c(line[x]);
					_map.set(x, y, c);
				}	

				y++;
			}
		} 
		else if(line == "MAP INFO")
		{
			int x, y;

			while(getline(file, line))
			{
				if(line == "END MAP INFO")
					break;
				
				int pos = line.find(delimiter);
				option  = line.substr(0, pos);
				value   = line.substr(pos+1, line.length());

				if(option == "x")
				{
					x = atoi(value.c_str());
				}
				else if(option == "y")
				{
					y = atoi(value.c_str());
				}
			}

			_map = Map(x, y);
		}
	}

	file.close();	
}

void Level::init(void)
{
	mkrooms();
	mkcorridors();
}

void Level::mkrooms(void)
{
	int roomsCount = (rand() % 10) + 4;

	int x, y, w, h, attempts;

	for(int i = 0; i < roomsCount; i++)
	{
		attempts = 0;

		do {
			w = 5 + rand() % 5;
			h = 5 + rand() % 5;
			x = (rand() % (_x - w - 1));
			y = (rand() % (_y - h - 1));
			
			attempts++;
		} while(overlaps(x, y, w, h) && attempts < MAX_SPACING_ATTEMPTS);
		
		if(attempts < MAX_SPACING_ATTEMPTS)
		{
			Room* r = new Room(x, y, w, h);
			_rooms.push_back(r);
		}
	}
	
	for(std::vector<Room*>::const_iterator it = _rooms.begin(); it != _rooms.end(); it++)
	{
		const Dimensions d = (*it)->get_dimensions();

		for(int x = d.x; x < d.x + d.w; x++)
		{
			for(int y = d.y; y < d.y + d.h; y++)
			{
				char c;
				if((*it)->is_corner(x, y))
				{
					c = Room::WALL_HORIZONTAL;
				}
				else if(x == d.x || x == d.x + d.w - 1)
				{
					c = Room::WALL_VERTICAL;
				}
				else if(y == d.y || y == d.y + d.h - 1)
				{
					c = Room::WALL_HORIZONTAL;
				}
				else
				{
					c = Room::ROOM_FLOOR;
				}
				
				_map.get(x, y).display(c);	
			}
		}		
	}
}

void Level::mkcorridors(void)
{
	int doors, x, y, z;
	for(std::vector<Room*>::const_iterator it = _rooms.begin(); it != _rooms.end(); it++)
	{
		const Dimensions dim = (*it)->get_dimensions();
		doors = 1 + (rand() % 5); 
		z = rand() % 2;
	
		for(int i = 0; i < doors; i++)
		{	
			// Get a random non-corner wall cell to be a door
			if(rand() % 2) // East or west
			{
				x = dim.x + ((dim.w - 1) * z);
				y = dim.y + ((rand() % (dim.h - 2)) + 1);
			}
			else // North or south
			{
				y = dim.y + ((dim.h - 1) * z);
				x = dim.x + ((rand() % (dim.w - 2)) + 1);
			}

			_map.get(x, y).display('+');
		}
	}
}

bool Level::overlaps(int x, int y, int w, int h) const
{
	for(std::vector<Room*>::const_iterator it = _rooms.begin(); it != _rooms.end();	it++)
	{
		const Dimensions d = (*it)->get_dimensions();
		
		if(
			(((x >= d.x) && (x <= (d.x + d.w))) ||
			((d.x >= x)  && (d.x <= (x + w))))  &&
			(((y >= d.y) && (y <= (d.y + d.h))) ||
			((d.y >= y)  && (d.y <= (y + h))))
		)
		{
			return true;
		}
	}

	return false;
}

void Level::draw(void) const
{
	//int i, x, y = 0;
	//for(std::vector<Cell*>::iterator it = _map.begin(); it != map.end(); it++)
	//{
	//	x = i / _x;
	//	y = i % _x;
	//	i++;
	//}
	//mvaddch(5,5, std::to_string(_map.height()).c_str()[0]);
	for(int y = 0; y < _map.height(); y++)
	for(int x = 0; x < _map.width(); x++)
	{
		mvaddch(y, x, _map.get(x, y).get_display());
	}

	//mvprintw(2, 0, "Rooms generated: %d", _rooms.size());
}
