#include "damage_system.h"

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

void DamageSystem::on_notify(const shared_ptr<Entity>& e, Event evt)
{
	switch(evt)
	{
		case Event::ENTITY_CREATED:
			break;
		case Event::ENTITY_COLLISION:
			if(e->has_component<Health>() && e->has_component<Collided>())
				add_entity(e);
			break;
	}
}
