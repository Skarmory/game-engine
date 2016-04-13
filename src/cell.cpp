#include "cell.h"

Cell::Cell(void) : _display('*')
{
}

Cell::Cell(char display) : _display(display)
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
