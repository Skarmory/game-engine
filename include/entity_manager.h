#ifndef entity_manager_h
#define entity_manager_h

#include <map>
#include <memory>
#include <string>

#include "entity.h"
#include "components.h"
#include "observer.h"
#include "entity_factory.h"

using namespace std;

class EntityManager : public Subject
{
public:
	
	EntityManager(void) {};

	//EntityManager(EntityManager const&)  = delete;
	//void operator=(EntityManager const&) = delete;

	//void create_entity(string entity_type);
	shared_ptr<Entity> create_entity(string entity_type);
	//void create_entity_at_loc(string entity_type, int x, int y);
	shared_ptr<Entity> create_entity_at_loc(string entity_type, int x, int y);
	void update(void);

private:
	map<int, shared_ptr<Entity>> _entities;
	EntityFactory _factory;

	static int NEXT_ID;
};

#endif
