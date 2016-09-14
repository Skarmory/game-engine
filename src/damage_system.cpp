#include "damage_system.h"

using namespace std;

void DamageSystem::init(EventManager& evm)
{
	evm.subscribe<CollisionEvent>(*this);
}

void DamageSystem::update(EventManager& evm)
{
	for(entity_iterator it = _entities.begin();	it != _entities.end();)
	{
		shared_ptr<Entity> e = it->lock();
		if(e != nullptr)
		{
			shared_ptr<Collided> cc = e->get_component<Collided>();
			shared_ptr<Health>   hc = e->get_component<Health>();

			for(auto& collided : cc->collided_with)
			{
				if(collided->has_component<Damage>())
				{
					hc->health -= collided->get_component<const Damage>()->damage;
				}
				else if(collided->has_component<PeriodicDamage>())
				{
					hc->health -= collided->get_component<const PeriodicDamage>()->damage;
				}
			}

			if(hc->health < 0)
			{
				e->obsolete = true;
			}
		}

		it = _entities.erase(it);
	}
}

void DamageSystem::receive(const CollisionEvent& event)
{
	if(event.e1->has_component<Health>() && (event.e2->has_component<Damage>() || event.e2->has_component<PeriodicDamage>()))
		add_entity(event.e1);

	if(event.e2->has_component<Health>() && (event.e1->has_component<Damage>() || event.e2->has_component<PeriodicDamage>()))
		add_entity(event.e2);
}
