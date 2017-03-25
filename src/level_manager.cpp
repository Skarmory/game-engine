#include "level_manager.h"

#include <random>
#include <sstream>
#include <fstream>

#include "environment.h"
#include "util.h"

LevelManager::LevelManager(void)
{
	Environment::get().get_event_manager()->subscribe<LevelTransitionEvent>(*this);
}

LevelManager::~LevelManager(void)
{
	for (auto& l : _levels)
		delete l.second;
}

Level& LevelManager::get_current(void) const
{
	return *_current;
}

void LevelManager::load(const string& name)
{
	if (_levels.find(name) == _levels.end())
		_load(name);
}

void LevelManager::_load(const string& name)
{
	mt19937 rng;
	rng.seed(random_device()());
	poisson_distribution<int> dist(6.75);
	std::stringstream sstream;
	std::string path, line, option, value, delimiter = "=";
	std::ifstream file;

	sstream << _path << name << ".dat";
	path = sstream.str();

	file.open(path);
	//assert(file.is_open());

	Level* l = new Level();

	while (getline(file, line))
	{
		// TODO: Figure out a decent file format
		if (line == "MAP INFO")
		{
			int x = 0, y = 0, z = 0;

			while (getline(file, line))
			{
				if (line == "END MAP INFO")
					break;

				size_t pos = line.find(delimiter);
				option = line.substr(0, pos);
				value = line.substr(pos + 1, line.length());

				if (option == "x")
					x = atoi(value.c_str());
				if (option == "y")
					y = atoi(value.c_str());
				if (option == "z")
					z = atoi(value.c_str());
			}

			l->_depth = z;
			l->_base_map = TerrainMap(x, y);
		}

		else if (line == "MAP DATA")
		{
			// TODO: Define "tilesets" of some description
			Color grass_fg_colour_map[9];
			Color grass_bg_colour_map[9];
			lerp_colour_map(grass_fg_colour_map, Color(0, 60, 0), Color(0, 200, 0), 9);
			lerp_colour_map(grass_bg_colour_map, Color(0, 10, 0), Color(0, 50, 0), 9);

			Color water_fg_colour_map[9];
			Color water_bg_colour_map[9];
			lerp_colour_map(water_fg_colour_map, Color(0, 0, 60), Color(0, 0, 200), 9);
			lerp_colour_map(water_fg_colour_map, Color(0, 0, 10), Color(0, 0, 50), 9);

			int y = 0;
			while (getline(file, line))
			{
				if (line == "END MAP DATA")
					break;

				for (int x = 0; x < l->_base_map.width(); x++)
				{
					char ch = line[x];
					bool walkable = false;
					bool blocks_los = false;
					Color fg, bg;

					switch (ch)
					{
					case '.':
						fg = grass_fg_colour_map[clamp(0, 8, dist(rng))];
						bg = grass_bg_colour_map[clamp(0, 8, dist(rng))];
						walkable = true;
						blocks_los = false;
						break;

					case '|':
					case '-':
						fg = Color(75, 75, 75);
						bg = Color(10, 10, 10);
						walkable = false;
						blocks_los = true;
						break;

					case '}':
						fg = water_fg_colour_map[clamp(0, 8, dist(rng))];
						bg = water_bg_colour_map[clamp(0, 8, dist(rng))];
						walkable = false;
						blocks_los = false;
						break;

					case '+':
						fg = colours_map.at("brown");
						bg = colours_map.at("dark_brown");
						walkable = true;
						blocks_los = false;
						break;
					}

					l->_base_map.set(x, y, new Cell(ch, fg, bg, walkable, blocks_los));
				}

				y++;
			}
		}
	}

	file.close();

	_levels[name] = l;

	if (_current == nullptr)
		_current = l;
}

void LevelManager::receive(const LevelTransitionEvent& e)
{
	load(e.level_transition->next_level_name);

	_current = _levels[e.level_transition->next_level_name];
}
