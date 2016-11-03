#ifndef ui_h
#define ui_h

#include "level.h"
#include "game_time.h"
#include "systems.h"


// Base UI element
class UIElement
{
public:
	UIElement(int x, int y, int w, int h) : _x(x), _y(y), _w(w), _h(h) {};
	virtual ~UIElement(void) {};

	virtual void draw(void) = 0;

protected:
	int _x, _y, _w, _h;
};


// Game world view
class Canvas : public UIElement
{
public:
	Canvas(int x, int y, int w, int h, Level* level, const EntityManager& entity_manager, const SystemManager& system_manager) : 
		UIElement(x, y, w, h), _level(level), _entity_manager(entity_manager), _system_manager(system_manager) {};

	void draw(void) override;
	pair<int, int> world_to_screen(int x, int y) const;
	pair<int, int> screen_to_world(int x, int y) const;

private:
	Level* _level;
	const EntityManager& _entity_manager;
	const SystemManager& _system_manager;

	int clamp(int low, int high, int value) const;
	pair<int, int> get_screen_origin(void)  const;
};



// Displays player attributes
class StatusDisplay : public UIElement
{
public:
	StatusDisplay(int x, int y, int w, int h, const EntityManager& entity_manager, const Timer& turn_timer, const int& turns) : 
		UIElement(x, y, w, h), _entity_manager(entity_manager), _turn_timer(turn_timer), _turns(turns) {};

	void draw(void) override;

private:
	const EntityManager& _entity_manager;
	const Timer& _turn_timer;
	const int& _turns;
};

// Inventory panel
class InventoryDisplay : public UIElement
{
public:
	InventoryDisplay(int x, int y, int w, int h) : UIElement(x, y, w, h) {}
	void draw(void) override;
};

#endif
