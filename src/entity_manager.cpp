#include "entity_manager.h"

using namespace std;

int EntityManager::NEXT_ID = 0;

shared_ptr<Entity> EntityManager::create_entity(string entity_type)
{
	/*
	shared_ptr<Entity> eptr = make_shared<Entity>(NEXT_ID);

	_entities[NEXT_ID] = eptr;

	notify(eptr, Event::EVENT_ENTITY_CREATED);

	NEXT_ID++;
	*/
	shared_ptr<Entity> e = _factory.create(NEXT_ID++, entity_type);
	notify(e, Event::EVENT_ENTITY_CREATED);	

	return e;
}

/*
void EntityManager::create_entity(string entity_type)
{
	shared_ptr<Entity> e = _factory.create(NEXT_ID++, entity_type);
	notify(e, Event::EVENT_ENTITY_CREATED);	
}
*/

shared_ptr<Entity> EntityManager::create_entity_at_loc(string entity_type, int x, int y)
{
	shared_ptr<Entity> e = create_entity(entity_type);
	shared_ptr<LocationComponent> loc = e->get_component<LocationComponent>();
	loc->x = x;
	loc->y = y;

	return e;
}

/*
void EntityManager::create_entity_at_loc(string entity_type, int x, int y)
{
	shared_ptr<Entity> e = create_entity(entity_type);
	shared_ptr<LocationComponent> loc = e->get_component<LocationComponent>();
	loc->x = x;
	loc->y = y;
}
*/

void EntityManager::update(void)
{
	for(map<int, shared_ptr<Entity>>::iterator it = _entities.begin(); it !=_entities.end();)
	{
		if(it->second->obsolete)
		{
			it = _entities.erase(it);
		}

		it++;
	}	
}
