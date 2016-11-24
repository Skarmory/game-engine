#ifndef ui_h
#define ui_h

#include <SFML/Graphics.hpp>

#include "level.h"
#include "game_time.h"
#include "systems.h"
#include "sprite.h"


// Base UI element
class UIElement
{
public:
	UIElement(RenderWindow& window, int x, int y, int w, int h) : _x(x), _y(y), _w(w), _h(h),  _window(window) {};
	virtual ~UIElement(void) = default;

	virtual void draw(void) = 0;

protected:
	int _x, _y, _w, _h;
	RenderWindow& _window;
};


// Game world view
class Canvas : public UIElement
{
public:
	Canvas(RenderWindow& window, int x, int y, int w, int h, Level* level, const EntityManager& entity_manager, const SystemManager& system_manager, const Texture& texture);

	void draw(void) override;
	pair<int, int> world_to_screen(int x, int y) const;
	pair<int, int> screen_to_world(int x, int y) const;

private:
	Level* _level;
	const EntityManager& _entity_manager;
	const SystemManager& _system_manager;
	const Texture& _texture;
	RenderTexture _rtexture;

	//int clamp(int low, int high, int value) const;
	pair<int, int> get_screen_origin(void)  const;
};



// Displays player attributes
class StatusDisplay : public UIElement
{
public:
	StatusDisplay(RenderWindow& window, int x, int y, int w, int h, const EntityManager& entity_manager, const Timer& turn_timer, const int& turns, const Font& font) :
		UIElement(window, x, y, w, h), _entity_manager(entity_manager), _turn_timer(turn_timer), _turns(turns), _font(font) {};

	void draw(void) override;

private:
	const EntityManager& _entity_manager;
	const Timer& _turn_timer;
	const int& _turns;
	const Font& _font;
};

// Inventory panel
class InventoryDisplay : public UIElement
{
public:
	InventoryDisplay(RenderWindow& window, int x, int y, int w, int h, const Font& font) : UIElement(window, x, y, w, h), _font(font) {}
	void draw(void) override;

private:
	const Font& _font;
};

#endif
