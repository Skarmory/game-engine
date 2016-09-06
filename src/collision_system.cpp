#include "collision_system.h"

using namespace std;

void CollisionSystem::update(void)
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

		shared_ptr<LocationComponent>  lc = e->get_component<LocationComponent>();
		shared_ptr<CollisionComponent> cc = e->get_component<CollisionComponent>();

		// Check for collision with other entities. Game is simple enough that no spatial hashing is necessary
		for(vector<weak_ptr<Entity>>::iterator check_it = it + 1;
				check_it != _entities.end();)
		{
			shared_ptr<Entity> check_e = check_it->lock();

			if(check_e == nullptr)
			{
				check_it = _entities.erase(check_it);
				continue;
			}

			shared_ptr<LocationComponent>  check_lc = check_e->get_component<LocationComponent>();
			shared_ptr<CollisionComponent> check_cc = check_e->get_component<CollisionComponent>();

			if(lc->x == check_lc->x && lc->y == check_lc->y)
			{
				if(e->has_component<CollidedComponent>())
					e->get_component<CollidedComponent>()->collided_with.push_back(check_e);
				else
					e->add_component(make_shared<CollidedComponent>(check_e));

				if(check_e->has_component<CollidedComponent>())
					check_e->get_component<CollidedComponent>()->collided_with.push_back(e);
				else
					check_e->add_component(make_shared<CollidedComponent>(e));

				notify(e, Event::ENTITY_COLLISION);
				notify(check_e, Event::ENTITY_COLLISION);
			}

			check_it++;
		}

		it++;
	}
}

void CollisionSystem::clean(void)
{
	for(vector<weak_ptr<Entity>>::iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> e;
		if((e = it->lock()) == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}

		if(e->has_component<CollidedComponent>())
			e->remove_component<CollidedComponent>();

		it++;
	}
}

void CollisionSystem::on_notify(const shared_ptr<Entity>& e, Event evt)
{
	switch(evt)
	{
		case Event::ENTITY_CREATED:
			if(e->has_component<CollisionComponent>() && e->has_component<LocationComponent>())
				add_entity(e);
		case Event::ENTITY_COLLISION:
			break;
	}
}
