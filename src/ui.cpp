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

Viewport::Viewport(int x, int y, int w, int h) : UIElement(x, y, w, h), sf::RenderWindow(VideoMode(640, 480), "Sovereign Incarnate", sf::Style::Resize), _screen_origin_x(0), _screen_origin_y(0)
{
	setKeyRepeatEnabled(false);
}

// Sets the world space coordinate origin of the screen coordinates, and updates the view.
void Viewport::update(void)
{
	const shared_ptr<const Location> loc = Environment::get().get_entity_manager()->get_player().get_component<Location>();
	const Level& level = Environment::get().get_level_manager()->get_current();

	_screen_origin_x = clamp(0.0f, (float)level.get_map_width() - (float)_w, loc->x - ((float)_w / 2.0f));
	_screen_origin_y = clamp(0.0f, (float)level.get_map_height() - (float)_h, loc->y - ((float)_h / 2.0f));

	std::pair<int, int> screen_coords = world_to_screen(_screen_origin_x, _screen_origin_y);

	_view.setCenter(screen_coords.first * 32.0f + ((_w / 2.0f) * 32.0f), screen_coords.second * 32.0f + ((_h / 2.0f) * 32.0f));
	_view.setSize(640.0f, 480.0f);
	setView(_view);
}

// Convert world space cell coordinates to screen space cell coordinates. (0, 0) is in the top left
pair<int, int> Viewport::world_to_screen(int x, int y) const
{
	return pair<int, int>(x - _screen_origin_x, y - _screen_origin_y);
}

// Convert screen space cell coordinates to world space cell coordinates.
pair<int, int> Viewport::screen_to_world(int x, int y) const
{
	return pair<int, int>(_screen_origin_x + x, _screen_origin_y + y);
}
