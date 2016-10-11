#ifndef cell_h
#define cell_h

#include "libtcod.hpp"

class Cell {
public:
	Cell(char disp, TCODColor fg, TCODColor bg, bool walkable);
	~Cell(void);

	char get_display(void) const;

	const TCODColor& get_foreground_colour(void) const;
	TCODColor& 		 get_foreground_colour(void);

	const TCODColor& get_background_colour(void) const;
	TCODColor&		 get_background_colour(void);

	bool is_walkable(void);
	bool is_walkable(void) const;
	
	bool 	  explored;
private:
	char 	  _display;
	TCODColor _foreground_colour;
	TCODColor _background_colour;
	bool      _walkable;
};

#endif
