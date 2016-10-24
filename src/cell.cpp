#include "cell.h"

Cell::Cell(char display, TCODColor fg, TCODColor bg, bool _is_walkable, bool _blocks_los) :
	_blocks_los(_blocks_los), _explored(false), _is_visible(false), _display(display), _foreground_colour(fg), _background_colour(bg), _is_walkable(_is_walkable), _light_value(0.0f), _light_saturation(0.0f)
{
}

char Cell::get_display(void) const
{
	return _display;
}

const TCODColor& Cell::get_foreground_colour(void) const
{
	return _foreground_colour;
}

TCODColor& Cell::get_foreground_colour(void)
{
	return _foreground_colour;
}

const TCODColor& Cell::get_background_colour(void) const
{
	return _background_colour;
}

TCODColor& Cell::get_background_colour(void)
{
	return _background_colour;
}
