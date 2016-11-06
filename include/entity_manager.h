#ifndef entity_manager_h
#define entity_manager_h

#include <map>
#include <memory>
#include <string>

#include "entity.h"
#include "components.h"
#include "entity_factory.h"
#include "events.h"

using namespace std;

class EntityManager
{
public:
	
	explicit EntityManager(const EventManager& evm) : _event_manager(evm)	{};

	shared_ptr<Entity> create_entity(string entity_type);
	shared_ptr<Entity> create_entity_at_loc(string entity_type, int x, int y);

	const Entity& get_player(void) const;
	
	void update(void);

private:
	map<int, shared_ptr<Entity>> _entities;
	const EventManager& _event_manager;
	EntityFactory _factory;
	int _player_id;

	static int NEXT_ID;
};

#endif
