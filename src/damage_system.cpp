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
			shared_ptr<Health>   hc;
			
			for(auto& collided : cc->collided_with)
			{
				if((hc = collided->get_component<Health>()) != nullptr && hc->is_alive)
				{
					int dmg = 0;

					if (e->has_component<PeriodicDamage>())
					{
						dmg = e->get_component<PeriodicDamage>()->damage;
					}
					else
					{
						dmg = e->get_component<Damage>()->damage;
					}

					hc->health -= dmg;

					if(hc->health < 0)
					{
						hc->is_alive = false;
					}
				}
			}
		}

		it = _entities.erase(it);
	}
}

void DamageSystem::receive(const CollisionEvent& event)
{
	if(event.e1->has_component<Damage>() || event.e1->has_component<PeriodicDamage>())
		add_entity(event.e1);

	if(event.e2->has_component<Damage>() || event.e2->has_component<PeriodicDamage>())
		add_entity(event.e2);
}
