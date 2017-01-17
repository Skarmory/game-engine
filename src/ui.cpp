#include "ui.h"

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

Camera::Camera(RenderWindow& window, int x, int y, int w, int h, const LevelManager& level_manager, const EntityManager& entity_manager, const SystemManager& system_manager, const Texture& texture) :
	UIElement(window, x, y, w, h), _world_x(0), _world_y(0), _level_manager(level_manager), _entity_manager(entity_manager), _system_manager(system_manager), _texture(texture)
{
	_rtexture.create(_w * 8, _h * 8);
}

void Camera::update(void)
{
	pair<int, int> world_coords = get_screen_origin();
	_world_x = world_coords.first;
	_world_y = world_coords.second;
}

void Camera::draw(void)
{
	const Map<sov::Glyph>& _map = _system_manager.get<RenderSystem>().get_composed_map();

	_rtexture.clear();

	Sprite s;
	RectangleShape rect(Vector2f(8, 8));

	s.setTexture(_texture);

	for (int x = 0; x < _w; x++)
	for (int y = 0; y < _h; y++)
	{
		const sov::Glyph& glyph = _map.get(x, y);

		int position = spritemap.at(glyph.glyph);
		int i = (position % 16) * 8;
		int j = (position / 16) * 8;

		
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

pair<int, int> Camera::world_to_screen(int x, int y) const
{
	return pair<int, int>(x - _world_x, y - _world_y);
}

pair<int, int> Camera::screen_to_world(int x, int y) const
{
	return pair<int, int>(_world_x + x, _world_y + y);
}

pair<int, int> Camera::get_screen_origin(void) const
{
	const shared_ptr<const Location> loc = _entity_manager.get_player().get_component<Location>();
	const Level& level = _level_manager.get_current();

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

void StatusDisplay::draw(void)
{
	Text text;
	int char_width = 16;
	text.setFont(_font);
	text.setString("Placeholder the Text Placeholder");
	text.setCharacterSize(char_width);
	text.setPosition(_x * 8.0f, _y * 8.0f);
	text.setFillColor(sf::Color::White);
	
	_window.draw(text);


	//TCODConsole::root->print(_x, _y, name.c_str());

	//text.setString("Stats will go here maybe");
	//text.setPosition(_x + (8 * 32) + 1, _y);
	//TCODConsole::root->print(_x + (name.length() + 1) , _y, stats.c_str());

	//TCODConsole::root->print(_x, _y + 1, "Turn timer:%.2f", _turn_timer.time_elapsed());
	//TCODConsole::root->print(_x + 16, _y + 1, "Turn:%i", _turns);
}

void InventoryDisplay::draw(void)
{
	//TCODConsole::root->print(_x + (_w / 2) - 5, _y, "Inventory");
}