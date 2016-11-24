#ifndef entity_factory_h
#define entity_factory_h

#include <string>
#include <map>

#include "components.h"

using namespace std;
using namespace sov;

class EntityFactory 
{
public:
	EntityFactory(void);
	
	unique_ptr<Entity> create(int id, string type);

private:
	map<string, unique_ptr<Entity> (EntityFactory::*)(int)> _create_methods;

	unique_ptr<Entity> create_player(int id);
	unique_ptr<Entity> create_fire(int id);
	unique_ptr<Entity> create_damage(int id);
	unique_ptr<Entity> create_aoe_dmg(int id);
};

#endif
