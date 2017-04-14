#include "light_system.h"

#include <cstdlib>
#include <algorithm>

#include "environment.h"
#include "light.h"
#include "location.h"
#include "level.h"

void LightSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);
}

void LightSystem::update(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for (int i = 0; i < _level.get_map_width(); i++)
	for (int j = 0; j < _level.get_map_height(); j++)
	{
		_level._base_map.get(i, j)->_light_value = 0.0f;
	}

	for (auto it = _entities.begin(); it != _entities.end();)
	{
		LightSource* light = (*it)->get_component<LightSource>();
		Location*    loc = (*it)->get_component<Location>();

		if (loc->z != _level._depth)
		{
			++it;
			continue;
		}

		int x0 = loc->x;
		int y0 = loc->y;
		int r = light->radius;
		float drop = light->dropoff;

		if (r > 0)
		{
			for (int i = 0; i < 8; i++)
				cast_light(x0, y0, r, 1, 1.0, 0.0, multipliers[0][i], multipliers[1][i], multipliers[2][i], multipliers[3][i], drop);

			_level._base_map.get(x0, y0)->_light_value = MAX_LIGHT_PERCENT;
		}

		++it;
	}
}

void LightSystem::cast_light(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy, float dropoff) {
	if (start_slope < end_slope) 
		return;

	double next_start_slope = start_slope;
	Level& _level = Environment::get().get_level_manager()->get_current();

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
			if (!_level.is_in_bounds(ax, 0) || !_level.is_in_bounds(0, ay)) 
				continue;

			int dx2dy2 = dx * dx + dy * dy;

			if (dx2dy2 < ((radius + 0.25f) * (radius + 0.25)))
			{
				float root_dx2dy2 = (float)sqrt(dx2dy2);
				float light_percent = max(MAX_LIGHT_PERCENT - root_dx2dy2 * dropoff, MIN_LIGHT_PERCENT);

				if (_level._base_map.get(ax, ay)->_light_value < light_percent)
					_level._base_map.get(ax, ay)->_light_value = light_percent;
			}

			if (blocked) 
			{
				if (_level.blocks_los(ax, ay)) 
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
			else if (_level.blocks_los(ax, ay)) 
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
