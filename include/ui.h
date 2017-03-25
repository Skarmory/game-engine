#ifndef ui_h
#define ui_h

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "game_time.h"

class sf::Font;
class sf::Texture;

// Base UI element
class UIElement
{
public:
	UIElement(sf::RenderWindow& window, float x, float y, float w, float h) : _x(x), _y(y), _w(w), _h(h),  _window(window) {};
	virtual ~UIElement(void) = default;

	virtual void draw(void) = 0;

	float get_width(void) const;
	float get_height(void) const;
	bool is_in_bounds(float x, float y) const;

protected:
	float _x, _y, _w, _h;
	sf::RenderWindow& _window;
};


// Game world view
class Camera : public UIElement
{
public:
	Camera(sf::RenderWindow& window, float x, float y, float w, float h, const sf::Texture& texture);

	void update(void);
	void draw(void) override;
	std::pair<float, float> world_to_screen(float x, float y) const;
	std::pair<float, float> screen_to_world(float x, float y) const;

private:
	float _world_x, _world_y;
	const sf::Texture& _texture;
	sf::RenderTexture _rtexture;

	std::pair<float, float> get_screen_origin(void)  const;
};


// Displays player attributes
class StatusDisplay : public UIElement
{
public:
	StatusDisplay(sf::RenderWindow& window, float x, float y, float w, float h, const Timer& turn_timer, const float& turns, const sf::Font& font) :
		UIElement(window, x, y, w, h), _turn_timer(turn_timer), _turns(turns), _font(font) {};

	void draw(void) override;

private:
	const Timer& _turn_timer;
	const float& _turns;
	const sf::Font& _font;
};

// Inventory panel
class InventoryDisplay : public UIElement
{
public:
	InventoryDisplay(sf::RenderWindow& window, float x, float y, float w, float h, const sf::Font& font) : UIElement(window, x, y, w, h), _font(font) {}
	void draw(void) override;

private:
	const sf::Font& _font;
};

#endif
