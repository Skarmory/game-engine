#ifndef cell_h
#define cell_h

#include "libtcod.hpp"
#include "graphic.h"

class Cell {
public:
	Cell(char display, TCODColor fg, TCODColor bg, bool walkable, bool blocks_los) : 
		_base_glyph(display, fg, bg), _glyph(display, fg, bg), _walkable(walkable), _blocks_los(blocks_los), _light_value(0.0f), _visible(false), _explored(false)  {}

	/*
	Cell(Glyph glyph, bool walkable, bool blocks_los) :
		_base_glyph(glyph), _glyph(glyph), _walkable(walkable), _blocks_los(blocks_los) {}
	*/

	/*
	char get_display(void) const;

	const TCODColor& get_foreground_colour(void) const;
	const TCODColor& get_background_colour(void) const;
	*/

	const Glyph& get_glyph(void) const;

	bool is_visible (void)  const;
	bool is_explored(void)  const;
	
private:
	/*
	char 	  _display;
	TCODColor _foreground_colour;
	TCODColor _background_colour;
	*/
	Glyph _base_glyph;
	Glyph _glyph;
	float _light_value;
	bool  _visible;
	bool  _blocks_los;
	bool  _explored;
	bool  _walkable;

	friend class Map;
	friend class Level;
	friend class RenderSystem;
};

#endif
