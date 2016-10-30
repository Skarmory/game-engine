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
	
	Cell& get(int x, int y);
	const Cell& get(int x, int y) const;

	void set(int x, int y, Cell* c);
	
	bool is_walkable(int x, int y) const;
	bool is_explored(int x, int y) const;

	void set_explored(int x, int y, bool explored);

private:
	friend class Level;

	std::vector<Cell*> _cells;
	int _width;
	int _height;
};

#endif
