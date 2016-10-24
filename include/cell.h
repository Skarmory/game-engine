#ifndef cell_h
#define cell_h

#include "libtcod.hpp"

class Cell {
public:
	Cell(char disp, TCODColor fg, TCODColor bg, bool walkable, bool los_blocker);

	char get_display(void) const;

	const TCODColor& get_foreground_colour(void) const;
	TCODColor& 		 get_foreground_colour(void);

	const TCODColor& get_background_colour(void) const;
	TCODColor&		 get_background_colour(void);
	
private:
	char 	  _display;
	TCODColor _foreground_colour;
	TCODColor _background_colour;
	float     _light_value;
	float	  _light_saturation;
	bool	  _is_visible;
	bool      _blocks_los;
	bool	  _explored;
	bool      _is_walkable;

	friend class Map;
	friend class Level;
};

#endif
