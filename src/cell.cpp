#include "cell.h"

const sov::Glyph& Cell::get_glyph(void) const
{
	return _glyph;
}

bool Cell::is_explored(void) const
{
	return _explored;
}

bool Cell::is_walkable(void) const
{
	return _walkable;
}

bool Cell::is_los_blocker(void) const
{
	return _los_blocker;
}