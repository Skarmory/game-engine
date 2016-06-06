#ifndef entity_manager_h
#define entity_manager_h

#include <map>
#include <memory>
#include "entity.h"

class EntityManager
{
public:
	EntityManager(void);
	~EntityManager(void);

	std::shared_ptr<Entity> create_entity(void);

private:
	std::map<int, std::shared_ptr<Entity>> _entities;

	static int NEXT_ID;
};

#endif
