#ifndef cell_h
#define cell_h

#include "libtcod.hpp"
#include "graphic.h"

class Cell {
public:
	Cell(char display, TCODColor fg, TCODColor bg, bool walkable, bool los_blocker) : 
		_glyph(display, fg, bg), 
		_walkable(walkable), _los_blocker(los_blocker),
		_explored(false)  {}

	const Glyph& get_glyph(void) const;

	bool is_explored(void) const;
	bool is_walkable(void) const;
	bool is_los_blocker(void) const;
	
private:
	Glyph _glyph;
	bool  _los_blocker;
	bool  _explored;
	bool  _walkable;

	friend class RenderSystem;
};

#endif
