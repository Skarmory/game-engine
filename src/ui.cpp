#include "ui.h"

void Canvas::draw(void)
{
	const Entity& player = _entity_manager.get_player();

	const shared_ptr<const Location> loc = player.get_component<Location>();
	int mx, my, mw, mh;

	mw = _level->get_map_width();
	mh = _level->get_map_height();

	pair<int, int> map_xy = get_screen_origin();
	mx = map_xy.first;
	my = map_xy.second;

	TCODConsole::root->clear();

	for (int x = _x; x < _x + _w; x++)
	for (int y = _y; y < _y + _h; y++)	
	{
		if (!_level->is_in_bounds(mx + x, my + y))
			continue;

		const Cell& cell = _level->get_cell(mx + x, my + y);

		const Glyph& glyph = cell.get_glyph();

		TCODConsole::root->putCharEx(x, y, glyph.glyph, glyph.fg_colour, glyph.bg_colour);
	}

	TCODConsole::flush();
}

pair<int, int> Canvas::world_to_screen(int x, int y) const
{
	pair<int, int> s0 = get_screen_origin();

	return pair<int, int>(s0.first - x, s0.second - y);
}

pair<int, int> Canvas::screen_to_world(int x, int y) const
{
	pair<int, int> s0 = get_screen_origin();

	return pair<int, int>(s0.first + x, s0.second + y);
}

int Canvas::clamp(int low, int high, int value) const
{
	if (value < low)
		return low;
	else if (value > high)
		return high;
	else
		return value;
}

pair<int, int> Canvas::get_screen_origin(void) const
{
	const shared_ptr<const Location> loc = _entity_manager.get_player().get_component<Location>();

	int x0 = 0, y0 = 0;

	if (_level->get_map_width() > _w)
	{
		x0 = clamp(0, _level->get_map_width() - _w, loc->x - (_w / 2));
	}

	if (_level->get_map_height() > _h)
	{
		y0 = clamp(0, _level->get_map_height() - _h, loc->y - (_h / 2));
	}

	return pair<int, int>(x0, y0);
}

void StatusDisplay::draw(void)
{

}