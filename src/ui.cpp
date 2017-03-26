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
using namespace sov;

float UIElement::get_width(void) const
{
	return _w;
}

float UIElement::get_height(void) const
{
	return _h;
}

bool UIElement::is_in_bounds(float x, float y) const
{
	return (0 <= x && x <= _w) && (0 <= y && y <= _h);
}

Camera::Camera(sf::RenderWindow& window, float x, float y, float w, float h, const sf::Texture& texture) :
	UIElement(window, x, y, w, h), _world_x(0), _world_y(0), _texture(texture)
{
	_rtexture.create(_w * 8, _h * 8);
}

void Camera::update(void)
{
	std::pair<float, float> world_coords = get_screen_origin();
	_world_x = world_coords.first;
	_world_y = world_coords.second;
}

void Camera::draw(void)
{
	const Map<sov::Glyph>& _map = Environment::get().get_system_manager()->get<RenderSystem>().get_composed_map();
	_rtexture.clear();

	Sprite s;
	RectangleShape rect(Vector2f(8, 8));

	s.setTexture(_texture);

	for (float x = 0; x < _w; x++)
	for (float y = 0; y < _h; y++)
	{
		const sov::Glyph& glyph = _map.get(x, y);

		int position = spritemap.at(glyph.glyph);
		float i = (position % 16) * 8;
		float j = (position / 16) * 8;

		
		s.setTextureRect(IntRect(i, j, 8, 8));

		s.setPosition((_x + x) * 8.0f, (_y + y) * 8.0f);
		rect.setPosition((_x + x) * 8.0f, (_y + y) * 8.0f);

		rect.setFillColor(glyph.bg_colour);
		s.setColor(glyph.fg_colour);

		_rtexture.draw(rect);
		_rtexture.draw(s);
	}

	const std::vector<RenderItem>& render_items = Environment::get().get_system_manager()->get<RenderSystem>().get_render_items();

	for (std::vector<RenderItem>::const_iterator it = render_items.begin(); it != render_items.end(); ++it)
	{
		RenderItem r = *it;

		float x = r.location.x;
		float y = r.location.y;

		const sov::Glyph& glyph = r.graphic.glyph;

		int position = spritemap.at(glyph.glyph);
		float i = (position % 16) * 8;
		float j = (position / 16) * 8;
		
		s.setTextureRect(IntRect(i, j, 8, 8));

		s.setPosition((_x + x) * 8.0f, (_y + y) * 8.0f);
		rect.setPosition((_x + x) * 8.0f, (_y + y) * 8.0f);

		rect.setFillColor(glyph.bg_colour);
		s.setColor(glyph.fg_colour);

		_rtexture.draw(rect);
		_rtexture.draw(s);

	}

	_rtexture.display();
	_window.draw(Sprite(_rtexture.getTexture()));
}

pair<float, float> Camera::world_to_screen(float x, float y) const
{
	return pair<float, float>(x - _world_x, y - _world_y);
}

pair<float, float> Camera::screen_to_world(float x, float y) const
{
	return pair<float, float>(_world_x + x, _world_y + y);
}

pair<float, float> Camera::get_screen_origin(void) const
{
	const shared_ptr<const Location> loc = Environment::get().get_entity_manager()->get_player().get_component<Location>();
	const Level& level = Environment::get().get_level_manager()->get_current();

	float x0 = 0, y0 = 0;

	if (level.get_map_width() > _w)
	{
		x0 = clamp((float) 0, level.get_map_width() - _w, loc->x - (_w / 2));
	}

	if (level.get_map_height() > _h)
	{
		y0 = clamp((float) 0, level.get_map_height() - _h, loc->y - (_h / 2));
	}

	return pair<float, float>(x0, y0);
}

void StatusDisplay::draw(void)
{
	Text text;
	float char_width = 16;
	text.setFont(_font);
	text.setString("Placeholder the Text Placeholder");
	text.setCharacterSize(char_width);
	text.setPosition(_x * 8.0f, _y * 8.0f);
	text.setFillColor(sf::Color::White);
	
	_window.draw(text);


	//TCODConsole::root->prfloat(_x, _y, name.c_str());

	//text.setString("Stats will go here maybe");
	//text.setPosition(_x + (8 * 32) + 1, _y);
	//TCODConsole::root->prfloat(_x + (name.length() + 1) , _y, stats.c_str());

	//TCODConsole::root->prfloat(_x, _y + 1, "Turn timer:%.2f", _turn_timer.time_elapsed());
	//TCODConsole::root->prfloat(_x + 16, _y + 1, "Turn:%i", _turns);
}

void InventoryDisplay::draw(void)
{
	//TCODConsole::root->prfloat(_x + (_w / 2) - 5, _y, "Inventory");
}