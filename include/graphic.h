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
		DAMAGE_EFFECT = 4
	};

	struct Glyph
	{
		Glyph(char glyph, Color fg_colour, Color bg_colour) : glyph(glyph), fg_colour(fg_colour), bg_colour(bg_colour) {}
		Glyph(void) : glyph(' '), fg_colour(Color::Black), bg_colour(Color::Black) {}
		Glyph(const Glyph& rhs)
		{
			glyph = rhs.glyph;
			fg_colour = rhs.fg_colour;
			bg_colour = rhs.bg_colour;
		}

		char glyph;
		Color fg_colour;
		Color bg_colour;
	};

	static const Glyph NULL_GLYPH;

	struct Graphic : public Component<Graphic>
	{
		Graphic(char graphic, Color fg_colour, Color bg_colour, DrawLayer layer) : glyph(graphic, fg_colour, bg_colour), layer(layer) {}
		Graphic(Glyph glyph, DrawLayer layer) : glyph(glyph), layer(layer) {}

		Glyph     glyph;
		DrawLayer layer;
	};
};

#endif
