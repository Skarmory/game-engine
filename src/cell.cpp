#include "cell.h"

/*
char Cell::get_display(void) const
{
	return _display;
}

const TCODColor& Cell::get_foreground_colour(void) const
{
	return _foreground_colour;
}

const TCODColor& Cell::get_background_colour(void) const
{
	return _background_colour;
}
*/

const Glyph& Cell::get_glyph(void) const
{
	return _glyph;
}

bool Cell::is_visible(void) const
{
	return _visible;
}

bool Cell::is_explored(void) const
{
	return _explored;
}
