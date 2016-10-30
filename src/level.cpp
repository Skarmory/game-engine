#include "level.h"

int Level::_NEXT = 0;

Level::Level(const EntityManager& em) : em(em)
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
				
				for(int x = 0; x < _map._width; x++)
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

					_map.set(x, y, new Cell(ch, fg, bg, walkable, blocks_los));
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

void Level::reset(void)
{
	for (int y = 0; y < _map._height; y++)
	for (int x = 0; x < _map._width; x++)
	{
		Cell& c = _map.get(x, y);
		
		c._glyph = c._base_glyph;
		c._light_value = 0.0f;
		c._visible = false;
	}
}

void Level::update(void)
{
	const shared_ptr<const Sight> sight  = em.get_player().get_component<Sight>();
	const shared_ptr<const Location> loc = em.get_player().get_component<Location>();

	if (sight->radius > 0)
	{
		_map.get(loc->x, loc->y)._visible = true;

		for (int i = 0; i < 8; i++)
			fov(loc->x, loc->y, sight->radius, 1, 1.0, 0.0, multipliers[0][i], multipliers[1][i], multipliers[2][i], multipliers[3][i]);
	}

	for (int y = 0; y < _map._height; y++)
	for (int x = 0; x < _map._width; x++)
	{
		Cell& c = _map.get(x, y);

		Glyph& base = c._base_glyph;

		float mod = c._visible ? c._light_value : c._explored ? MIN_LIGHT_PERCENT : 0.0f;

		c._glyph.fg_colour.setHSV(base.fg_colour.getHue(), base.fg_colour.getSaturation() * mod, base.fg_colour.getValue() * mod);
		c._glyph.bg_colour.setHSV(base.bg_colour.getHue(), base.bg_colour.getSaturation() * mod, base.bg_colour.getValue() * mod);
	}
}

void Level::fov(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy) 
{
	if (start_slope < end_slope) 
		return;
	

	double next_start_slope = start_slope;

	for (int i = row; i <= radius; i++) 
	{
		bool blocked = false;

		for (int dx = -i, dy = -i; dx <= 0; dx++) 
		{
			double l_slope = (dx - 0.5) / (dy + 0.5);
			double r_slope = (dx + 0.5) / (dy - 0.5);

			if (start_slope < r_slope)
				continue;
			else if (end_slope > l_slope)
				break;

			int sax = dx * xx + dy * xy;
			int say = dx * yx + dy * yy;

			if ((sax < 0 && (int)std::abs(sax) > x) || (say < 0 && (int)std::abs(say) > y))
				continue;

			int ax = x + sax;
			int ay = y + say;
			if (!is_in_bounds(ax, 0) || !is_in_bounds(0, ay))
				continue;

			int radius2 = radius * radius;
			int dx2dy2 = dx * dx + dy * dy;

			if ((int)dx2dy2 < radius2 + (0.25f * radius2))
			{
				Cell& c = _map.get(ax, ay);
				c._visible = true;

				if (c._light_value > MIN_LIGHT_PERCENT && !c._explored)
					c._explored = true;
			}

			if (blocked)
			{
				if(blocks_los(ax, ay))
				{
					next_start_slope = r_slope;
					continue;
				}
				else
				{
					blocked = false;
					start_slope = next_start_slope;
				}
			}
			else if (blocks_los(ax, ay))
			{
				blocked = true;
				next_start_slope = r_slope;
				fov(x, y, radius, i + 1, start_slope, l_slope, xx, xy, yx, yy);
			}
		}

		if (blocked)
			break;
	}
}

void Level::set_cell_light(int x, int y, float value, bool force)
{
	if(is_in_bounds(x, y))
	{
		if (value > _map.get(x, y)._light_value || force)
		{
			_map.get(x, y)._light_value = value;
		}
	}
}

float Level::get_cell_light(int x, int y) const
{
	return _map.get(x, y)._light_value;
}

bool Level::is_walkable(int x, int y) const
{
	return _map.is_walkable(x, y);
}

bool Level::is_explored(int x, int y) const
{
	return _map.is_explored(x, y);
}

bool Level::is_visible(int x, int y) const
{
	return _map.get(x, y)._visible;
}

bool Level::is_in_bounds(int x, int y) const
{
	return (x >= 0 && x < _map._width && y >= 0 && y < _map._height);
}

bool Level::blocks_los(int x, int y) const
{
	return _map.get(x, y)._blocks_los;
}

int Level::get_map_width(void) const
{
	return _map._width;
}

int Level::get_map_height(void) const
{
	return _map._height;
}

const Cell& Level::get_cell(int x, int y) const
{
	return _map.get(x, y);
}