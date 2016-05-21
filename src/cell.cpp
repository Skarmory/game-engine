#include "cell.h"

Cell::Cell(void) : _display('*')
{
}

Cell::Cell(char display, bool walkable) : _display(display), _walkable(walkable)
{
}

Cell::~Cell(void)
{
}

char Cell::get_display(void) const
{
	return _display;
}

void Cell::display(char c)
{
	_display = c;
}

bool Cell::is_walkable(void) const
{
	return _walkable;
}
