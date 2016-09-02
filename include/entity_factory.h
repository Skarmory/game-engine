#ifndef entity_factory_h
#define entity_factory_h

#include <string>
#include <map>

#include "libtcod.hpp"
#include "components.h"

using namespace std;

class EntityFactory 
{
public:
	EntityFactory(void);
	~EntityFactory(void) {}
	
	shared_ptr<Entity> create(int id, string type);

private:
	map<string, shared_ptr<Entity> (EntityFactory::*)(int)> _create_methods;

	shared_ptr<Entity> create_player(int id);

	shared_ptr<Entity> create_fire(int id);

	shared_ptr<Entity> create_damage(int id);
};

#endif
