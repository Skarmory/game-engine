#include "damage_system.h"

void DamageSystem::update(void)
{
	for(std::vector<std::weak_ptr<Entity>>::iterator it = _entities.begin();
			it != _entities.end(); it++)
	{
		std::shared_ptr<Entity> e = it->lock();

		if(e == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}
		
		std::shared_ptr<CollidedComponent> cc = e->get_component<CollidedComponent>();
	    std::shared_ptr<HealthComponent>   hc = e->get_component<HealthComponent>();

		const std::shared_ptr<const DamageComponent> dc = cc->collided_with.get_component<const DamageComponent>();

		if(hc != nullptr && dc != nullptr)
		{
			hc->health -= dc->damage;
		}

		e->remove_component<CollidedComponent>();
	}

	_entities.clear();
}
