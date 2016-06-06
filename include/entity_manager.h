#ifndef entity_manager_h
#define entity_manager_h

#include <map>
#include <memory>
#include "entity.h"

class EntityManager
{
public:
	
	static EntityManager& get_instance(void)
	{
		static EntityManager instance;

		return instance;
	}

	EntityManager(EntityManager const&)  = delete;
	void operator=(EntityManager const&) = delete;

	std::shared_ptr<Entity> create_entity(void);

private:
	EntityManager(void) {};
	std::map<int, std::shared_ptr<Entity>> _entities;

	static int NEXT_ID;
};

#endif
