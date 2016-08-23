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
	TCODRandom* default_gen = TCODRandom::getInstance();

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
			TCODColor fg_colour_map[9];
			TCODColor bg_colour_map[9];
			TCODColor fg_interpolate[] = { TCODColor::green, TCODColor::darkestGreen };
			TCODColor bg_interpolate[] = { TCODColor(0,50,0), TCODColor(0,10,0) };
			int keys[] = {0, 8};
			TCODColor::genMap(fg_colour_map, 2, fg_interpolate, keys);
			TCODColor::genMap(bg_colour_map, 2, bg_interpolate, keys);

			int y = 0;
			while(getline(file, line))
			{
				if(line == "END MAP DATA")
					break;
				
				for(int x = 0; x < _map.width(); x++)
				{
					char ch = line[x];
					bool b = true;
					TCODColor fg = fg_colour_map[default_gen->getInt(0, 8, 6)];
					TCODColor bg = bg_colour_map[default_gen->getInt(0, 8, 6)];

					if(ch != '.')
					{
						b = false;
						fg = TCODColor::darkGrey;
						bg = TCODColor(10,10,10);
					}

					_map.set(x, y, new Cell(ch, fg, bg, b));
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
		Cell& cell = _map.get(x, y);
		TCODConsole::root->putCharEx(x, y, cell.get_display(), cell.get_foreground_colour(), cell.get_background_colour());
	}
}

bool Level::is_walkable(int x, int y) const
{
	return _map.is_walkable(x, y);
}

bool Level::is_in_bounds(int x, int y) const
{
	return (x >= 0 && x < _map.width() && y >= 0 && y < _map.height());
}
