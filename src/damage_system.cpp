#include "damage_system.h"

#include <exception>

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
				
		if(e->has_component<HealthComponent>() && e->has_component<CollidedComponent>())
		{
			std::shared_ptr<CollidedComponent> cc = e->get_component<CollidedComponent>();
			std::shared_ptr<HealthComponent>   hc = e->get_component<HealthComponent>();
			const std::shared_ptr<const DamageComponent> dc = cc->collided_with.get_component<const DamageComponent>();

			hc->health -= dc->damage;
		}

		e->remove_component<CollidedComponent>();
	}

	//_entities.clear();
}
