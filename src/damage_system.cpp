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
					int dmg = e->get_component<Damage>()->damage;


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
	if(event.e1->has_component<Damage>())
		add_entity(event.e1);

	if(event.e2->has_component<Damage>())
		add_entity(event.e2);
}
