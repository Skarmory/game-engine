#include "ui.h"

void Canvas::draw(void)
{
	const Entity& player = _entity_manager.get_player();

	const shared_ptr<const Location> loc = player.get_component<Location>();
	int mx, my, mw, mh;

	mw = _level->get_map_width();
	mh = _level->get_map_height();

	
	pair<int, int> map_xy = screen_to_world(0, 0);
	mx = map_xy.first;
	my = map_xy.second;
	

	// Clamp the viewable map x and y to: 0 <= x|y <= (mw - _w | mh - _h)
	//mx = (loc->x - _w / 2 <= 0) ? 0 : (loc->x + _w / 2 >= mw) ? (mw - _w) : (loc->x - _w / 2);
	//my = (loc->y - _h / 2 <= 0) ? 0 : (loc->y + _h / 2 >= mh) ? (mh - _h) : (loc->y - _h / 2);

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
	const shared_ptr<const Location> loc = _entity_manager.get_player().get_component<Location>();

	int sx_orig = loc->x - _w / 2;
	int sy_orig = loc->y - _h / 2;

	return pair<int, int>(x - sx_orig, y - sx_orig);
}

pair<int, int> Canvas::screen_to_world(int x, int y) const
{
	const shared_ptr<const Location> loc = _entity_manager.get_player().get_component<Location>();

	int sx_orig, sy_orig;

	if (_level->get_map_width() > _w)
	{
		if (loc->x - (_w / 2) < 0)
			sx_orig = 0;
		else if (loc->x + (_w / 2) > _level->get_map_width())
			sx_orig = _level->get_map_width() - _w;
		else
			sx_orig = loc->x - (_w / 2);
	}
	else
	{
		sx_orig = 0;
	}

	if (_level->get_map_height() > _h)
	{
		if (loc->y - (_h / 2) < 0)
			sy_orig = 0;
		else if (loc->y + (_h / 2) > _level->get_map_height())
			sy_orig = _level->get_map_height() - _h;
		else
			sy_orig = loc->y - (_h / 2);
	}
	else
	{
		sy_orig = 0;
	}

	return pair<int, int>(x + sx_orig, y + sy_orig);
}

void StatusDisplay::draw(void)
{

}