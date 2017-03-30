#include "entity_manager.h"

#include <sstream>
#include <fstream>

#include "environment.h"
#include "location.h"

using namespace std;

EntityLoader::~EntityLoader(void)
{
	for (auto& loader : _component_loaders)
		delete loader.second;
}

unique_ptr<Entity> EntityLoader::load(const string& entity_id)
{
	std::unique_ptr<Entity> ptr(new Entity(-1));
	std::ifstream fs;
	std::string line, option, value;

	fs.open(_file_path);

	bool found = false;

	while (!found && std::getline(fs, line))
	{
		// Skip comments and blank lines
		if (line[0] == '#' || line.find_first_not_of(' ') == std::string::npos)
			continue;

		size_t position = line.find('=');
		option = line.substr(0, position);
		value = line.substr(position + 1, line.length());

		if (option == "name" && value == entity_id)
			found = true;
	}

	if (!found)
	{
		std::stringstream ss;
		ss << "Could not find data for: " << entity_id;
		throw std::runtime_error(ss.str().c_str());
	}

	_component_loaders["location"]->load(*ptr, "");

	while (line.find_first_not_of(' ') != std::string::npos)
	{
		std::getline(fs, line);

		size_t position = line.find('=');
		option = line.substr(0, position);
		value = line.substr(position + 1, line.length());

		if (_component_loaders.find(option) != _component_loaders.end())
			_component_loaders[option]->load(*ptr, value);
	}

	return ptr;
}

bool EntityCache::_has(const string& entity_id)
{
	return _entities.find(entity_id) != _entities.end();
}

unique_ptr<Entity> EntityCache::get_entity(const string& entity_id)
{
	if(!_has(entity_id))
	{
		_load(entity_id);
	}

	return unique_ptr<Entity>(new Entity(*_entities[entity_id]));
}

void EntityCache::_load(const string& entity_id)
{
	_entities[entity_id] = _loader.load(entity_id);
}

int EntityManager::NEXT_ID = 0;

shared_ptr<Entity> EntityManager::create_entity(const string& entity_type)
{
	shared_ptr<Entity> e(_cache.get_entity(entity_type));
	e->_id = NEXT_ID;
	_entities[NEXT_ID] = e;

	if (entity_type == "player")
		_player_id = NEXT_ID;

	NEXT_ID++;

	Environment::get().get_event_manager()->broadcast<EntityCreated>(e);

	return e;
}

shared_ptr<Entity> EntityManager::create_entity_at_loc(const string& entity_type, int x, int y, int z)
{
	shared_ptr<Entity> e = create_entity(entity_type);
	shared_ptr<Location> loc = e->get_component<Location>();
	loc->x = x;
	loc->y = y;
	loc->z = z;

	return e;
}

void EntityManager::update(void)
{
	for(map<int, shared_ptr<Entity>>::iterator it = _entities.begin(); it !=_entities.end();)
	{
		if(it->second->obsolete)
		{
			it = _entities.erase(it);
			continue;
		}

		++it;
	}	
}

const Entity& EntityManager::get_player(void) const
{
	return *_entities.at(_player_id);
}

Entity& EntityManager::get_player(void)
{
	return *_entities.at(_player_id);
}

// TODO: Spatial partitioning of some kind
vector<shared_ptr<Entity>> EntityManager::get_entities_at_loc(int x, int y, int z) const
{
	vector<shared_ptr<Entity>> ret;

	for (auto& entity : _entities)
	{
		shared_ptr<Location> lc = entity.second->get_component<Location>();

		if (lc->x == x && lc->y == y && lc->z == z)
			ret.push_back(entity.second);
	}

	return ret;
}
