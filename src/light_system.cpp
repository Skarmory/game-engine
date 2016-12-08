#include "light_system.h"

void LightSystem::init(EventManager& em)
{
	em.subscribe<EntityCreated>(*this);
}

void LightSystem::update(EventManager& em)
{
	for (int i = 0; i < _level->get_map_width(); i++)
	for (int j = 0; j < _level->get_map_height(); j++)
	{
		_level->_base_map.get(i, j)->_light_value = 0.0f;
	}

	for (entity_iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> e;
		if (!(e = it->lock()))
		{
			it = _entities.erase(it);
			continue;
		}

		shared_ptr<LightSource> light = e->get_component<LightSource>();
		shared_ptr<Location>    loc = e->get_component<Location>();
		int x0 = loc->x;
		int y0 = loc->y;
		int r = light->radius;
		float drop = light->dropoff;

		if (r > 0)
		{
			for (int i = 0; i < 8; i++)
				cast_light(x0, y0, r, 1, 1.0, 0.0, multipliers[0][i], multipliers[1][i], multipliers[2][i], multipliers[3][i], drop);

			_level->_base_map.get(x0, y0)->_light_value = MAX_LIGHT_PERCENT;
		}

		it++;
	}
}

void LightSystem::cast_light(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy, float dropoff) {
	if (start_slope < end_slope) 
		return;

	double next_start_slope = start_slope;

	for (int i = row; i <= radius; i++) 
	{

		bool blocked = false;

		for (int dx = -i, dy = -i; dx <= 0; dx++) 
		{

			double l_slope = (dx - 0.5) / (dy + 0.5);
			double r_slope = (dx + 0.5) / (dy - 0.5);

			if (start_slope < r_slope)
				continue;
			else if (end_slope > l_slope)
				break;

			int sax = dx * xx + dy * xy;
			int say = dx * yx + dy * yy;

			if ((sax < 0 && (int)std::abs(sax) > x) || (say < 0 && (int)std::abs(say) > y))
				continue;

			int ax = x + sax;
			int ay = y + say;
			if (!_level->is_in_bounds(ax, 0) || !_level->is_in_bounds(0, ay)) 
				continue;

			int dx2dy2 = dx * dx + dy * dy;
			float root_dx2dy2 = (float)sqrt(dx2dy2);

			if (root_dx2dy2 < radius + 0.25f)
			{
				float light_percent = max(MAX_LIGHT_PERCENT - root_dx2dy2 * dropoff, MIN_LIGHT_PERCENT);

				if (_level->_base_map.get(ax, ay)->_light_value < light_percent)
					_level->_base_map.get(ax, ay)->_light_value = light_percent;
			}

			if (blocked) 
			{
				if (_level->blocks_los(ax, ay)) 
				{
					next_start_slope = r_slope;
					continue;
				}
				else 
				{
					blocked = false;
					start_slope = next_start_slope;
				}
			}
			else if (_level->blocks_los(ax, ay)) 
			{
				blocked = true;
				next_start_slope = r_slope;
				cast_light(x, y, radius, i + 1, start_slope, l_slope, xx, xy, yx, yy, dropoff);
			}
		}

		if (blocked)
			break;
	}
}

void LightSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<LightSource>())
		add_entity(event.entity);
}
