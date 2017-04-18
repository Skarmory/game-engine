#include "cell.h"

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