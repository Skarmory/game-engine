#include "cell.h"

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

bool Cell::is_walkable(void) const
{
	return _walkable;
}