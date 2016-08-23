#ifndef cell_h
#define cell_h

#include "libtcod.hpp"

class Cell {
public:
	Cell(char, TCODColor, TCODColor, bool);
	~Cell(void);

	char 	  get_display(void) const;
	TCODColor get_foreground_colour(void) const;
	TCODColor get_background_colour(void) const;
	bool 	  is_walkable(void) const;

private:
	char 	  _display;
	TCODColor _foreground_colour;
	TCODColor _background_colour;
	bool      _walkable;
};

#endif
