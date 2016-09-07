#include "damage_system.h"

using namespace std;

void DamageSystem::update(const EventManager& evm)
{
	for(vector<weak_ptr<Entity>>::iterator it = _entities.begin();
			it != _entities.end();)
	{
		shared_ptr<Entity> e = it->lock();

		if(e == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}
			
		shared_ptr<Collided> cc = e->get_component<Collided>();
		shared_ptr<Health>   hc = e->get_component<Health>();

		for(vector<shared_ptr<Entity>>::iterator c_it = cc->collided_with.begin(); c_it != cc->collided_with.end(); c_it++)
		{
			if((*c_it)->has_component<Damage>())
			{
				hc->health -= (*c_it)->get_component<const Damage>()->damage;
			}
		}

		if(hc->health < 0)
			e->obsolete = true;

		it = _entities.erase(it);
	}
}

void DamageSystem::receive(const CollisionEvent& event)
{
	if(event.e1->has_component<Health>() && event.e1->has_component<Collided>())
		add_entity(event.e1);

	if(event.e2->has_component<Health>() && event.e2->has_component<Collided>())
		add_entity(event.e2);
}
