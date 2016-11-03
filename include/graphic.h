#ifndef graphic_component_h
#define graphic_component_h

#include "component.h"
#include "libtcod.hpp"

enum DrawLayer 
{
	EFFECT   = 0,
	OBJECT   = 1,
	ITEM     = 2,
	CREATURE = 3,
	AREADMG  = 4
};

struct Glyph
{
	Glyph(char glyph, TCODColor fg_colour, TCODColor bg_colour) : glyph(glyph), fg_colour(fg_colour), bg_colour(bg_colour)  {}
	Glyph(void) : glyph(' '), fg_colour(TCODColor::black), bg_colour(TCODColor::black) {}

	char glyph;
	TCODColor fg_colour;
	TCODColor bg_colour;
};

struct Graphic : public Component
{
	Graphic(char graphic, TCODColor fg_colour, TCODColor bg_colour, DrawLayer layer) : glyph(graphic, fg_colour, bg_colour), layer(layer) {}
	Graphic(Glyph glyph, DrawLayer layer) : glyph(glyph), layer(layer) {}

	Glyph     glyph;
	DrawLayer layer;
};

#endif
