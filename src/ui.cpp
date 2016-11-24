#include "ui.h"

Canvas::Canvas(RenderWindow& window, int x, int y, int w, int h, Level* level, const EntityManager& entity_manager, const SystemManager& system_manager, const Texture& texture) :
	UIElement(window, x, y, w, h), _level(level), _entity_manager(entity_manager), _system_manager(system_manager), _texture(texture)
{
	_rtexture.create(_w * 8, _h * 8);
}

void Canvas::draw(void)
{
	const Entity& player   = _entity_manager.get_player();
	const Map<sov::Glyph>& _map = _system_manager.get<RenderSystem>().get_composed_map();

	const shared_ptr<const Location> loc = player.get_component<Location>();
	int mx, my, mw, mh;

	mw = _level->get_map_width();
	mh = _level->get_map_height();

	pair<int, int> map_xy = get_screen_origin();
	mx = map_xy.first;
	my = map_xy.second;

	_rtexture.clear();

	Sprite s;
	RectangleShape rect(Vector2f(8, 8));

	for (int x = _x; x < _x + _w; x++)
	for (int y = _y; y < _y + _h; y++)	
	{
		if (!_level->is_in_bounds(mx + x, my + y))
			continue;

		const sov::Glyph& glyph = _map.get((mx + x), (my + y));

		int position = spritemap.at(glyph.glyph);
		int i = (position % 16) * 8;
		int j = (position / 16) * 8;

		s.setTexture(_texture);
		s.setTextureRect(IntRect(i, j, 8, 8));

		s.setPosition(x * 8, y * 8);
		rect.setPosition(x * 8, y * 8);

		rect.setFillColor(glyph.bg_colour);
		s.setColor(glyph.fg_colour);

		_rtexture.draw(rect);
		_rtexture.draw(s);
	}

	_rtexture.display();
	_window.draw(Sprite(_rtexture.getTexture()));
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
	Text text;
	int char_width = 16;
	text.setFont(_font);
	text.setString("Placeholder the Text Placeholder");
	text.setCharacterSize(char_width);
	text.setPosition(_x * 8, _y * 8);
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