#include "collision_system.h"

#include "environment.h"
#include "collided.h"
#include "location.h"
#include "collision.h"

using namespace std;
using namespace sov;

void CollisionSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);	
}

void CollisionSystem::update(void)
{
	_clean();

	for(auto it = _entities.begin();	it != _entities.end();)
	{
		Location*  lc = (*it)->get_component<Location>();
		Collision* cc = (*it)->get_component<Collision>();
		
		if(!cc->enabled)
		{
			++it;
			continue;
		}

		// Check for collision with other entities. Game is simple enough that no spatial hashing is necessary
		for(auto check_it = it + 1; check_it != _entities.end();)
		{
			Location*  check_lc = (*check_it)->get_component<Location>();
			Collision* check_cc = (*check_it)->get_component<Collision>();

			if(!check_cc->enabled)
			{
				++check_it;
				continue;
			}

			if(lc->x == check_lc->x && lc->y == check_lc->y)
			{
				if((*it)->has_component<Collided>())
					(*it)->get_component<Collided>()->collided_with.push_back((*check_it));
				else
					(*it)->add_component(new Collided(*check_it));

				if((*check_it)->has_component<Collided>())
					(*check_it)->get_component<Collided>()->collided_with.push_back((*it));
				else
					(*check_it)->add_component(new Collided(*it));

				Environment::get().get_event_manager()->broadcast<CollisionEvent>((*it), (*check_it));
			}

			++check_it;
		}

		++it;
	}
}

void CollisionSystem::_clean(void)
{
	for(auto it = _entities.begin(); it != _entities.end();)
	{
		if((*it)->has_component<Collided>())
			(*it)->remove_component<Collided>();

		++it;
	}
}

void CollisionSystem::receive(const EntityCreated& e)
{
	if(e.entity->has_component<Collision>() && e.entity->has_component<Location>())
		add_entity(e.entity);
}
