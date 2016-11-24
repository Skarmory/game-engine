#ifndef graphic_component_h
#define graphic_component_h

#include "colour.h"
#include "component.h"

namespace sov
{

	enum DrawLayer
	{
		EFFECT = 0,
		OBJECT = 1,
		ITEM = 2,
		CREATURE = 3,
		AREADMG = 4
	};

	struct Glyph
	{
		Glyph(char glyph, Color fg_colour, Color bg_colour) : glyph(glyph), fg_colour(fg_colour), bg_colour(bg_colour) {}
		Glyph(void) : glyph(' '), fg_colour(Color::Black), bg_colour(Color::Black) {}

		char glyph;
		Color fg_colour;
		Color bg_colour;
	};

	struct Graphic : public Component
	{
		Graphic(char graphic, Color fg_colour, Color bg_colour, DrawLayer layer) : glyph(graphic, fg_colour, bg_colour), layer(layer) {}
		Graphic(Glyph glyph, DrawLayer layer) : glyph(glyph), layer(layer) {}

		Glyph     glyph;
		DrawLayer layer;
	};

};

#endif
