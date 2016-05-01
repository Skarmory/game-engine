#include "level.h"

int Level::_NEXT = 0;

Level::Level(void)
{
	_level = ++Level::_NEXT;
}

Level::~Level(void)
{
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
					char ch = line[x];
					_map.set(x, y, new Cell(ch));
					assert(_map.get(x, y).get_display() == ch);
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

void Level::draw(void) const
{
	for(int y = 0; y < _map.height(); y++)
	for(int x = 0; x < _map.width(); x++)
	{
		mvaddch(y, x, _map.get(x, y).get_display());
	}

	mvprintw(0, 0, "Map: %i, %i", _map.width(), _map.height());
}
