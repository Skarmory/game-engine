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
		int _x = 0;
		int _y = 0;

		while(x >= y)
		{
			_y = y0 + y;
			for(int _x = x0; _x <= x0 + x; _x++)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);
			for(int _x = x0; _x >= x0 - x; _x--)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);
			
			_y = y0 - y;
			for(int _x = x0; _x <= x0 + x; _x++)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);
			for(int _x = x0; _x >= x0 - x; _x--)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);


			_x = x0 + y;
			for(int _y = y0; _y <= y0 + x; _y++)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);
			for(int _y = y0; _y >= y0 - x; _y--)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);
			
			_x = x0 - y;
			for(int _y = y0; _y <= y0 + x; _y++)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);
			for(int _y = y0; _y >= y0 - x; _y--)
				_level->set_cell_light(_x, _y, 1.0f, 1.0f);

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
