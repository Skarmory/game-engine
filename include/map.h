#ifndef map_h
#define map_h

#include <string>
#include <vector>
#include "cell.h"

class Map {
public:
	Map(void);
	Map(int x, int y);

	~Map(void);
	
	Cell& get(int x, int y) const;
	void  set(int x, int y, Cell* c);

	int   width(void) const;
	int   height(void) const;

	bool is_walkable(int x, int y) const;

private:
	std::vector<Cell*> _cells;
	int _x_max;
	int _y_max;
};

#endif
