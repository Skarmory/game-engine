#ifndef cell_h
#define cell_h

#include "graphic.h"

class Cell 
{
public:
	Cell(char display, Color fg, Color bg, bool walkable, bool los_blocker) :
		_glyph(display, fg, bg), _light_value(0.0f),
		_walkable(walkable), _los_blocker(los_blocker),
		_explored(false), _visible(false) {}

	const sov::Glyph& get_glyph(void) const;
	float get_light_value(void) const;

	bool is_explored(void) const;
	bool is_visible(void) const;
	bool is_walkable(void) const;
	bool is_los_blocker(void) const;

private:
	sov::Glyph _glyph;
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
