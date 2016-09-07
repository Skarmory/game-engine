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
	
	explicit EntityManager(EventManager& evm) : _event_manager(evm)
	{};

	shared_ptr<Entity> create_entity(string entity_type);
	shared_ptr<Entity> create_entity_at_loc(string entity_type, int x, int y);
	
	void update(void);

private:
	map<int, shared_ptr<Entity>> _entities;
	EventManager& _event_manager;
	EntityFactory _factory;

	static int NEXT_ID;
};

#endif
