#include "cell.h"

Cell::Cell(char display, TCODColor fg, TCODColor bg, bool walkable) : explored(false), _display(display), _foreground_colour(fg), _background_colour(bg), _walkable(walkable), _light_value(1.0f) 
{
}

Cell::~Cell(void)
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

void Cell::set_light_value(float value)
{
	_light_value = value;
}

float Cell::get_light_value(void)
{
	return _light_value;
}

void Cell::set_light_saturation(float saturation)
{
	_light_saturation = saturation;
}

float Cell::get_light_saturation(void)
{
	return _light_saturation;
}

bool Cell::is_walkable(void)
{
	return _walkable;
}

bool Cell::is_walkable(void) const
{
	return _walkable;
}

/*
bool Cell::is_explored(void) const
{
	return _explored;
}
*/
