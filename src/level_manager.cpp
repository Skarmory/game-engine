#include "level_manager.h"

#include <sstream>
#include <fstream>

#include "graphics.h"
#include "environment.h"

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
	std::stringstream sstream;
	std::string path, line, option, value, delimiter = "=";
	std::ifstream file;

	sstream << _path << name;
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
					x = stoi(value);
				if (option == "y")
					y = stoi(value);
				if (option == "z")
					z = stoi(value);
			}

			l->_depth = z;
			l->_base_map = TerrainMap(x, y);
		}

		else if (line == "MAP DATA")
		{
			// TODO: Define "tilesets" of some description

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
					sov::Graphics gfx;

					switch (ch)
					{
					case '.':
						gfx.sprite = sf::Sprite(*Environment::get().get_sprite_cache()->get("grass2.png"));
						gfx.layer = sov::DrawLayer::EFFECT;
						gfx.brightness = 0.0f;

						walkable = true;
						blocks_los = false;
						break;

					case '[':
					case ']':
					case '_':
					case '-':
						gfx.sprite = sf::Sprite(*Environment::get().get_sprite_cache()->get("stone-wall2.png"));
						gfx.layer = sov::DrawLayer::EFFECT;
						gfx.brightness = 0.0f;
						
						if (ch == '-' || ch == '_')
							gfx.sprite_transform.rotate(90.0f);

						walkable = false;
						blocks_los = true;
						break;

					case '0':
					case '1':
					case '2':
					case '3':

						gfx.sprite = sf::Sprite(*Environment::get().get_sprite_cache()->get("stone-wall-corner2.png"));
						gfx.layer = sov::DrawLayer::EFFECT;
						gfx.brightness = 0.0f;

						if (ch == '1')
							gfx.sprite_transform.rotate(90.0f);
						else if (ch == '3')
							gfx.sprite_transform.rotate(180.0f);
						else if (ch == '2')
							gfx.sprite_transform.rotate(270.0f);

						walkable = false;
						blocks_los = true;

						break;
					}

					l->_base_map.set(x, y, new Cell(gfx, walkable, blocks_los));
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
