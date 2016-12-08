#include "cell.h"

const sov::Glyph& Cell::get_glyph(void) const
{
	return _glyph;
}

float Cell::get_light_value(void) const
{
	return _light_value;
}

bool Cell::is_explored(void) const
{
	return _explored;
}

bool Cell::is_visible(void) const
{
	return _visible;
}

bool Cell::is_walkable(void) const
{
	return _walkable;
}

bool Cell::is_los_blocker(void) const
{
	return _los_blocker;
}