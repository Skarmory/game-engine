#include "collision_system.h"

using namespace std;

void CollisionSystem::init(EventManager& evm)
{
	evm.subscribe<EntityCreated>(*this);	
}

void CollisionSystem::update(EventManager& evm)
{
	clean();

	for(entity_iterator it = _entities.begin();	it != _entities.end();)
	{
		shared_ptr<Entity> e = it->lock();

		if(e == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}

		shared_ptr<Location>  lc = e->get_component<Location>();
		shared_ptr<Collision> cc = e->get_component<Collision>();
		
		if(!cc->enabled)
		{
			++it;
			continue;
		}

		// Check for collision with other entities. Game is simple enough that no spatial hashing is necessary
		for(entity_iterator check_it = it + 1; check_it != _entities.end();)
		{
			shared_ptr<Entity> check_e = check_it->lock();

			if(check_e == nullptr)
			{
				check_it = _entities.erase(check_it);
				continue;
			}

			shared_ptr<Location>  check_lc = check_e->get_component<Location>();
			shared_ptr<Collision> check_cc = check_e->get_component<Collision>();

			if(!check_cc->enabled)
			{
				++check_it;
				continue;
			}

			if(lc->x == check_lc->x && lc->y == check_lc->y)
			{
				if(e->has_component<Collided>())
					e->get_component<Collided>()->collided_with.push_back(check_e);
				else
					e->add_component(make_shared<Collided>(check_e));

				if(check_e->has_component<Collided>())
					check_e->get_component<Collided>()->collided_with.push_back(e);
				else
					check_e->add_component(make_shared<Collided>(e));

				evm.broadcast<CollisionEvent>(e, check_e);
			}

			++check_it;
		}

		++it;
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

		if(e->has_component<Collided>())
			e->remove_component<Collided>();

		++it;
	}
}

void CollisionSystem::receive(const EntityCreated& e)
{
	if(e.entity->has_component<Collision>() && e.entity->has_component<Location>())
		add_entity(e.entity);
}
