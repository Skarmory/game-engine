#include "entity_manager.h"

int EntityManager::NEXT_ID = 0;

EntityManager::EntityManager(void) {}

EntityManager::~EntityManager(void) {}

std::shared_ptr<Entity> EntityManager::create_entity(void)
{
	std::shared_ptr<Entity> eptr = std::make_shared<Entity>(NEXT_ID);

	_entities[NEXT_ID] = eptr;

	return eptr;
}
