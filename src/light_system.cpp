#include "light_system.h"

void LightSystem::init(EventManager& em)
{
	em.subscribe<EntityCreated>(*this);
}

void LightSystem::update(EventManager& em)
{
	for(entity_iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> e;
		if(!(e = it->lock()))
		{
			it = _entities.erase(it);
			continue;
		}

		shared_ptr<LightSource> light = e->get_component<LightSource>();
		shared_ptr<Location>    loc   = e->get_component<Location>();
		int x0 = loc->x;
		int y0 = loc->y;

		int x = light->radius;
		int y = 0;	
		int err = 0;

		while(x >= y)
		{
			for(int _x = x0; _x <= (x0 + x); _x++)
			{
				//(100.0 - (abs(_x - x0) * light->dropoff))
				if(_level->is_in_bounds(_x, y0 + y))
					_level->set_cell_light(_x, y0 + y, 5.0f);

				if(_level->is_in_bounds(_x, y0 - y))
					_level->set_cell_light(_x, y0 - y, 5.0f);

				if(_level->is_in_bounds(x0 + y, _x))
					_level->set_cell_light(x0 + y, _x, 5.0f);

				if(_level->is_in_bounds(x0 - y, _x))
					_level->set_cell_light(x0 - y, _x, 5.0f);
				
				int __x = abs(x0 - _x);

				if(_level->is_in_bounds(x0 - __x, y0 + y))
					_level->set_cell_light(x0 - __x, y0 + y, 5.0f);

				if(_level->is_in_bounds(x0 - __x, y0 - y))
					_level->set_cell_light(x0 - __x, y0 - y, 5.0f);

				if(_level->is_in_bounds(x0 + y, x0 - __x))
					_level->set_cell_light(x0 + y, x0 - __x, 5.0f);

				if(_level->is_in_bounds(x0 - y, x0 - __x))
					_level->set_cell_light(x0 - y, x0 - __x, 5.0f);
			}

			// Math
			y   += 1;
			err += 1 + (2 * y);

			if(2 * (err - x) + 1 > 0)
			{
				x   -= 1;
				err += 1 - (2 * x);
			}
		}

		it++;
	}
}

void LightSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<LightSource>())
		add_entity(event.entity);
}
