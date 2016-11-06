#include "level.h"

int Level::_NEXT = 0;

Level::Level(const EntityManager& em) : em(em)
{
	_level = ++Level::_NEXT;
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
				
				for(int x = 0; x < _base_map.width(); x++)
				{
					char ch = line[x];
					bool walkable = true;
					bool blocks_los = false;

					TCODColor fg = fg_colour_map[default_gen->getInt(0, 8, 6)];
					TCODColor bg = bg_colour_map[default_gen->getInt(0, 8, 6)];

					if(ch != '.')
					{
						walkable = false;
						blocks_los = true;
						fg = TCODColor::darkGrey;
						bg = TCODColor(10,10,10);
					}

					_base_map.set(x, y, new Cell(ch, fg, bg, walkable, blocks_los));
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
					x = atoi(value.c_str());
				if(option == "y")
					y = atoi(value.c_str());
			}

			_base_map   = TerrainMap(x, y);
			_vision_map = Map<short>(x, y);
			_light_map  = Map<float>(x, y);
		}
	}

	file.close();	
}

bool Level::is_walkable(int x, int y) const
{
	return _base_map.is_walkable(x, y);
}

bool Level::is_explored(int x, int y) const
{
	return _base_map.is_explored(x, y);
}

bool Level::is_in_bounds(int x, int y) const
{
	return (x >= 0 && x < _base_map.width() && y >= 0 && y < _base_map.height());
}

bool Level::blocks_los(int x, int y) const
{
	return _base_map.get(x, y)->is_los_blocker();
}

int Level::get_map_width(void) const
{
	return _base_map.width();
}

int Level::get_map_height(void) const
{
	return _base_map.height();
}

const Cell& Level::get_cell(int x, int y) const
{
	return *_base_map.get(x, y);
}