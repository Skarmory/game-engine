#include "ui.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "environment.h"

#include "graphic.h"
#include "render_system.h"
#include "level.h"
#include "sprite.h"
#include "location.h"
#include "map.h"
#include "util.h"


using namespace sf;
using namespace std;

int UIElement::get_width(void) const
{
	return _w;
}

int UIElement::get_height(void) const
{
	return _h;
}

bool UIElement::is_in_bounds(int x, int y) const
{
	return (0 <= x && x <= _w) && (0 <= y && y <= _h);
}

Viewport::Viewport(int x, int y, int w, int h) : UIElement(x, y, w, h), sf::RenderWindow(VideoMode(640, 480), "Sovereign Incarnate"), _world_x(0), _world_y(0)
{
	setKeyRepeatEnabled(false);
}

void Viewport::update(void)
{
	std::pair<int, int> world_coords = get_screen_origin();
	_world_x = world_coords.first;
	_world_y = world_coords.second;
}

pair<int, int> Viewport::world_to_screen(int x, int y) const
{
	return pair<int, int>(x - _world_x, y - _world_y);
}

pair<int, int> Viewport::screen_to_world(int x, int y) const
{
	return pair<int, int>(_world_x + x, _world_y + y);
}

pair<int, int> Viewport::get_screen_origin(void) const
{
	const shared_ptr<const Location> loc = Environment::get().get_entity_manager()->get_player().get_component<Location>();
	const Level& level = Environment::get().get_level_manager()->get_current();

	int x0 = 0, y0 = 0;

	if (level.get_map_width() > _w)
	{
		x0 = clamp(0, level.get_map_width() - _w, loc->x - (_w / 2));
	}

	if (level.get_map_height() > _h)
	{
		y0 = clamp(0, level.get_map_height() - _h, loc->y - (_h / 2));
	}

	return pair<int, int>(x0, y0);
}