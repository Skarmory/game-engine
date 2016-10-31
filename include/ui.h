#ifndef ui_h
#define ui_h

#include "level.h"

class UIElement
{
public:
	UIElement(int x, int y, int w, int h) : _x(x), _y(y), _w(w), _h(h) {};
	virtual ~UIElement(void) {};

	virtual void draw(void) = 0;

protected:
	int _x, _y, _w, _h;
};

class Canvas : public UIElement
{
public:
	Canvas(int x, int y, int w, int h, Level* level, const EntityManager& entity_manager) : UIElement(x, y, w, h), _level(level), _entity_manager(entity_manager) {};
	void draw(void) override;
	pair<int, int> world_to_screen(int x, int y) const;
	pair<int, int> screen_to_world(int x, int y) const;

private:
	Level* _level;
	const EntityManager& _entity_manager;

	int clamp(int low, int high, int value) const;
	pair<int, int> get_screen_origin(void) const;
};

class StatusDisplay : public UIElement
{
public:
	StatusDisplay(int x, int y, int w, int h, const EntityManager& entity_manager) : UIElement(x, y, w, h), _entity_manager(entity_manager) {};
	void draw(void) override;

private:
	const EntityManager& _entity_manager;
};

#endif
