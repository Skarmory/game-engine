#ifndef entity_manager_h
#define entity_manager_h

#include <map>
#include <memory>
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

	unique_ptr<Entity> load(const string& entity_id);

private:
	const std::string _file_path = "resources/data/entities.txt";

	map<string, ComponentLoader*>  _component_loaders = {
		{ "graphic", new GraphicLoader() },
		{ "location", new LocationLoader() },
		{ "collision", new CollisionLoader() },
		{ "health", new HealthLoader() },
		{ "light", new LightSourceLoader() },
		{ "sight", new SightLoader() },
		{ "damage", new DamageLoader() },
		{ "levelTransition", new LevelTransitionLoader() }
	};
};

//

class EntityCache
{
public:
	unique_ptr<Entity> get(const string& entity_id);

private:
	EntityLoader _loader;
	map<string, unique_ptr<Entity>> _entities;

	void _load(const string& entity_id);
	bool _has(const string& entity_id);
};

class EntityManager
{
public:
	
	explicit EntityManager(void) : _player_id(-1) {};

	shared_ptr<Entity> create_entity(const string& entity_type);
	shared_ptr<Entity> create_entity_at_loc(const string& entity_type, int x, int y, int z);

	const std::shared_ptr<Entity>& get_player(void) const;
	std::shared_ptr<Entity>& get_player(void);
	vector<shared_ptr<Entity>> get_entities_at_loc(int x, int y, int z) const;
	
	void update(void);

private:
	map<int, shared_ptr<Entity>> _entities;
	EntityCache _cache;
	int _player_id;

	static int NEXT_ID;
};

#endif
