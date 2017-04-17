#include "damage_system.h"

#include "environment.h"
#include "collided.h"
#include "health.h"
#include "damage.h"

using namespace std;
using namespace sov;

void DamageSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<CollisionEvent>(*this);
}

void DamageSystem::update(void)
{
	for(auto it = _entities.begin();	it != _entities.end();)
	{
		Collided* cc = (*it)->get_component<Collided>();
		
		for(auto& collided : cc->collided_with)
		{
			Health* hc;
			if((hc = collided->get_component<Health>()) != nullptr && hc->is_alive)
			{
				int dmg = (*it)->get_component<Damage>()->damage;

				hc->health -= dmg;

				if(hc->health < 0)
					hc->is_alive = false;
			}
		}
		

		it = _entities.erase(it);
	}
}

void DamageSystem::receive(const CollisionEvent& event)
{
	if(event.e1->has_component<Damage>())
		_entities.push_back(event.e1);

	if(event.e2->has_component<Damage>())
		_entities.push_back(event.e2);
}
