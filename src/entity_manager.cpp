#include "entity_manager.h"

int EntityManager::NEXT_ID = 0;

std::shared_ptr<Entity> EntityManager::create_entity(void)
{
	std::shared_ptr<Entity> eptr = std::make_shared<Entity>(NEXT_ID);

	_entities[NEXT_ID] = eptr;

	return eptr;
}

void EntityManager::update(void)
{
	for(std::map<int, shared_ptr<Entity>>::iterator it = _entities.begin(); it !=_entities.end();)
	{
		if(it->second->obsolete)
		{
			it = _entities.erase(it);
		}

		it++;
	}	
}
