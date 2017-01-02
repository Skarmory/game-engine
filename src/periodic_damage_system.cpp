#include "periodic_damage_system.h"

void PeriodicDamageUpdateSystem::init(EventManager& evm)
{
	evm.subscribe<EntityCreated>(*this);
}

void PeriodicDamageUpdateSystem::update(EventManager& evm)
{
	for(entity_iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> entity = it->lock();
		if(entity == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}

		shared_ptr<PeriodicDamage> p_dmg = entity->get_component<PeriodicDamage>();
		shared_ptr<Collision> collision = entity->get_component<Collision>();

		p_dmg->current_turns++;
		
		if(p_dmg->current_turns == p_dmg->per_turns)
		{
			if(!collision->enabled)
				collision->enabled = true;
			p_dmg->current_turns = 0;
		}
		else if(collision->enabled)
		{
			collision->enabled = false;
		}

		++it;
	}
}

void PeriodicDamageUpdateSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<PeriodicDamage>() && event.entity->has_component<Collision>())
		add_entity(event.entity);
}
