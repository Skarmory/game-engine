#include "visibility_system.h"

#include "environment.h"
#include "sight.h"
#include "location.h"
#include "level.h"

void VisibilitySystem::init(void) {}

void VisibilitySystem::update(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for (int i = 0; i < _level.get_map_width(); i++)
	for (int j = 0; j < _level.get_map_height(); j++)
	{
		_level._base_map.get(i, j)->_visible = false;
	}

	const shared_ptr<const Sight> sight  = Environment::get().get_entity_manager()->get_player()->get_component<Sight>();
	const shared_ptr<const Location> loc = Environment::get().get_entity_manager()->get_player()->get_component<Location>();

	if (sight->radius > 0)
	{
		_level._base_map.get(loc->x, loc->y)->_visible = true;

		for (int i = 0; i < 8; i++)
			calculate_fov(loc->x, loc->y, sight->radius, 1, 1.0, 0.0, multipliers[0][i], multipliers[1][i], multipliers[2][i], multipliers[3][i]);
	}
}

void VisibilitySystem::calculate_fov(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy)
{
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

			if (dx2dy2 < (radius + 0.25f) * (radius + 0.25f))
			{
				_level._base_map.get(ax, ay)->_visible = true;
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
				calculate_fov(x, y, radius, i + 1, start_slope, l_slope, xx, xy, yx, yy);
			}
		}

		if (blocked)
			break;
	}
}