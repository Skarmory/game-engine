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

					fg.setSaturation(0.2);
					bg.setSaturation(0.2);

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

void Level::base_draw(void)
{
	for(int y = 0; y < _map.height(); y++)
	for(int x = 0; x < _map.width(); x++)
		set_cell_light(x, y, 0.1f, 0.1f);

	draw();
}

void Level::draw(void)
{
	for(int y = 0; y < _map.height(); y++)
	for(int x = 0; x < _map.width(); x++)
	{
		Cell& cell = _map.get(x, y);

		TCODColor fg = cell.get_foreground_colour();
		TCODColor bg = cell.get_background_colour();

		fg.setValue(fg.getValue() * cell.get_light_value());
		bg.setValue(bg.getValue() * cell.get_light_value());

		fg.setSaturation(fg.getSaturation() * cell.get_light_saturation());
		bg.setSaturation(bg.getSaturation() * cell.get_light_saturation());

		TCODConsole::root->putCharEx(x, y, cell.get_display(), fg, bg);
	}
}

void Level::set_cell_light(int x, int y, float value, float saturation)
{
	if(is_in_bounds(x, y))
	{
		_map.get(x, y).set_light_value(value);
		_map.get(x, y).set_light_saturation(saturation);
	}
}


bool Level::is_walkable(int x, int y) const
{
	return _map.is_walkable(x, y);
}

bool Level::is_walkable(int x, int y)
{
	return _map.is_walkable(x, y);
}

bool Level::is_explored(int x, int y) const
{
	return _map.is_explored(x, y);
}

bool Level::is_explored(int x, int y)
{
	return _map.is_explored(x, y);
}

bool Level::is_in_bounds(int x, int y) const
{
	return (x >= 0 && x < _map.width() && y >= 0 && y < _map.height());
}


void Level::set_explored(int x, int y, bool explored) 
{
	_map.set_explored(x, y, explored);
}

/*
void Level::set_light_intensity(int x, int y, float intensity)
{
	_map.set_light_intensity(x, y, intensity);
}
*/
