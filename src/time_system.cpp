#include "time_system.h"

using namespace std;

void TimeSystem::update(void)
{
	for(vector<weak_ptr<Entity>>::iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> e;
		shared_ptr<TimedLifeComponent> tlc;

		if((e = it->lock()) == nullptr)
		{
			it = _entities.erase(it);
			continue;	
		}

		if((tlc = e->get_component<TimedLifeComponent>()) != nullptr)
		{
			tlc->turns_passed++;
			tlc->expires_in--;

			if(tlc->expires_in == 0)
				e->obsolete = true;
		}

		it++;
	}
}
