#include "damage_system.h"

#include <exception>

using namespace std;

void DamageSystem::update(void)
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
			
		shared_ptr<CollidedComponent> cc = e->get_component<CollidedComponent>();
		shared_ptr<HealthComponent>   hc = e->get_component<HealthComponent>();

		for(vector<shared_ptr<Entity>>::iterator c_it = cc->collided_with.begin(); c_it != cc->collided_with.end(); c_it++)
		{
			if((*c_it)->has_component<DamageComponent>())
			{
				hc->health -= (*c_it)->get_component<const DamageComponent>()->damage;
			}
		}

		if(hc->health < 0)
			e->obsolete = true;

		it++;
	}
}

void DamageSystem::on_notify(const shared_ptr<Entity>& e, Event evt)
{
	switch(evt)
	{
		case Event::ENTITY_COLLISION:
			if(e->has_component<HealthComponent>())
				add_entity(e);
			break;
	}
}
