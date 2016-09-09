#include "time_system.h"

using namespace std;

void TimeSystem::update(const EventManager& evm)
{
	for(vector<weak_ptr<Entity>>::iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> e;
		shared_ptr<TimedLife> tlc;

		if((e = it->lock()) == nullptr)
		{
			it = _entities.erase(it);
			continue;	
		}

		if((tlc = e->get_component<TimedLife>()) != nullptr)
		{
			tlc->turns_passed++;
			tlc->expires_in--;

			if(tlc->expires_in <= 0)
				e->obsolete = true;
		}

		it++;
	}
}

void TimeSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<TimedLife>())
		add_entity(event.entity);
}
