#ifndef cell_h
#define cell_h

#include "graphics.h"

class Cell 
{
public:
	Cell(int x, int y, sov::Graphics graphic, bool walkable, bool los_blocker) :
		_graphic(graphic), _los_blocker(los_blocker),
		_explored(false), _visible(false), _walkable(walkable),
		_x(x), _y(y) {}

	bool is_explored(void) const;
	bool is_visible(void) const;
	bool is_walkable(void) const;
	bool is_los_blocker(void) const;

private:
	sov::Graphics _graphic;
	bool  _los_blocker;
	bool  _explored;
	bool  _visible;
	bool  _walkable;
	int _x, _y;

	friend class RenderSystem;
	friend class LightSystem;
	friend class VisibilitySystem;
};

#endif
