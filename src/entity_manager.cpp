#include "entity_manager.h"

using namespace std;

EntityLoader::EntityLoader(void)
{
	_file = unique_ptr<rapidxml::file<>>(new rapidxml::file<>(_file_path));
	_xml_data.parse<0>(_file->data());
}

EntityLoader::~EntityLoader(void)
{
	for (auto& loader : _component_loaders)
		delete loader.second;
}

unique_ptr<Entity> EntityLoader::load(const string& entity_id)
{
	unique_ptr<Entity> ptr(new Entity(-1));

	auto node = _xml_data.first_node();

	while (node)
	{
		if (node->first_attribute()->value() == entity_id)
			break;

		node = node->next_sibling();
	}

	auto child_node = node->first_node();
	while (child_node)
	{
		string node_name = child_node->name();
		if (_component_loaders.find(node_name) != _component_loaders.end())
			_component_loaders[node_name]->load(child_node, *ptr);
		
		child_node = child_node->next_sibling();
	}

	return ptr;
}

bool EntityCache::_has_entity(string entity_id)
{
	if(_entities.find(entity_id) != _entities.end())
		return true;
	return false;
}

unique_ptr<Entity> EntityCache::get_entity(string entity_id)
{
	if(!_has_entity(entity_id))
	{
		_load_entity(entity_id);
	}

	return unique_ptr<Entity>(new Entity(*_entities[entity_id]));
}

void EntityCache::_load_entity(const string& entity_id)
{
	_entities[entity_id] = _loader.load(entity_id);
}

int EntityManager::NEXT_ID = 0;

shared_ptr<Entity> EntityManager::create_entity(const string& entity_type)
{
	//shared_ptr<Entity> e(move(_factory.create(NEXT_ID, entity_type)));
	shared_ptr<Entity> e(_cache.get_entity(entity_type));
	e->_id = NEXT_ID;
	_entities[NEXT_ID] = e;

	if (entity_type == "player")
		_player_id = NEXT_ID;

	NEXT_ID++;

	_event_manager.broadcast<EntityCreated>(e);

	return e;
}

shared_ptr<Entity> EntityManager::create_entity_at_loc(const string& entity_type, int x, int y)
{
	shared_ptr<Entity> e = create_entity(entity_type);
	shared_ptr<Location> loc = e->get_component<Location>();
	loc->x = x;
	loc->y = y;

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

		it++;
	}	
}

const Entity& EntityManager::get_player(void) const
{
	return *_entities.at(_player_id);
}
