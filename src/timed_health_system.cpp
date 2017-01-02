#include "timed_health_system.h"

void TimedHealthSystem::init(EventManager& evm)
{
	evm.subscribe<EntityCreated>(*this);
}

void TimedHealthSystem::update(EventManager& evm)
{
	for(entity_iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> entity = it->lock();
		if(entity == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}

		shared_ptr<TimedHealth> timed_health = entity->get_component<TimedHealth>();
		timed_health->remaining--;

		if(timed_health->remaining == 0)
			entity->obsolete = true;

		++it;
	}
}

void TimedHealthSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<TimedHealth>())
		add_entity(event.entity);
}
