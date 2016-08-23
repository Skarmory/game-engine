#include "cell.h"

Cell::Cell(char display, TCODColor fg, TCODColor bg,  bool walkable) : _display(display), _foreground_colour(fg), _background_colour(bg), _walkable(walkable)
{
}

Cell::~Cell(void)
{
}

char Cell::get_display(void) const
{
	return _display;
}

TCODColor Cell::get_foreground_colour(void) const
{
	return _foreground_colour;
}

TCODColor Cell::get_background_colour(void) const
{
	return _background_colour;

}
bool Cell::is_walkable(void) const
{
	return _walkable;
}
