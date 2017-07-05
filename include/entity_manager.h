#ifndef entity_manager_h
#define entity_manager_h

#include <unordered_map>
#include <string>

#include "entity.h"
#include "events.h"
#include "loaders.h"

// Temporary loading code

class EntityLoader
{
public:
	explicit EntityLoader(void) {}
	~EntityLoader(void);

	Entity* load(const std::string& entity_id);

private:
	const std::string _file_path = "resources/data/entities.txt";

	std::unordered_map<std::string, ComponentLoader*>  _component_loaders = {
		{ "graphic", new GraphicLoader() },
		{ "location", new LocationLoader() },
		{ "collision", new CollisionLoader() },
		{ "health", new HealthLoader() },
		{ "light", new LightSourceLoader() },
		{ "sight", new SightLoader() },
		{ "damage", new DamageLoader() },
		{ "levelTransition", new LevelTransitionLoader() },
		{ "animation", new AnimatorLoader() }
	};
};

//

class EntityCache
{
public:
	Entity* get(const std::string& entity_id);

private:
	EntityLoader _loader;
	std::unordered_map<std::string, Entity*> _entities;

	void _load(const std::string& entity_id);
	bool _has(const std::string& entity_id);
};

class EntityManager
{
public:
	
	explicit EntityManager(void) : _player_id(-1) {};
	~EntityManager(void);

	Entity* create_entity(const string& entity_type);
	Entity* create_entity_at_loc(const string& entity_type, int x, int y, int z);

	const Entity* get_player(void) const;
	Entity* get_player(void);
	std::vector<Entity*> get_entities_at_loc(int x, int y, int z) const;
	
	void update(void);

private:
	std::unordered_map<int, Entity*> _entities;
	EntityCache _cache;
	int _player_id;

	static int NEXT_ID;
};

#endif
