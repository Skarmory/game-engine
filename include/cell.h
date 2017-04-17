#ifndef cell_h
#define cell_h

#include "graphics.h"

class Cell 
{
public:
	Cell(sov::Graphics graphic, bool walkable, bool los_blocker) :
		_graphic(graphic), _light_value(0.0f),
		_los_blocker(los_blocker),
		_explored(false), _visible(false), _walkable(walkable) {}

	float get_light_value(void) const;

	bool is_explored(void) const;
	bool is_visible(void) const;
	bool is_walkable(void) const;
	bool is_los_blocker(void) const;

private:
	sov::Graphics _graphic;
	float _light_value;
	bool  _los_blocker;
	bool  _explored;
	bool  _visible;
	bool  _walkable;

	friend class RenderSystem;
	friend class LightSystem;
	friend class VisibilitySystem;
};

#endif
