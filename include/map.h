#ifndef map_h
#define map_h

#include <vector>
#include "cell.h"

template<class T>
class Map 
{
/* Class which "wraps" a 1D vector and masquerades as a 2D vector */
public:
	Map(void) : _width(0), _height(0), _items(0) {}
	Map(int width, int height) : _width(width), _height(height), _items(width * height) {}

	virtual ~Map(void) = default;

	size_t size(void)   const { return _items.size(); }
	int width(void)  const { return _width; }
	int height(void) const { return _height; }
	
	const T& get(int x, int y) const { return _items.at((y * _width) + x); }
	T&       get(int x, int y)       { return _items.at((y * _width) + x); }

	void set(int x, int y, const T& value) { _items[(y * _width) + x] = value; }

protected:
	int _width;
	int _height;

	std::vector<T> _items;
};

class TerrainMap : public Map<Cell*>
{
public:
	TerrainMap(void) : Map<Cell*>() {}
	TerrainMap(int width, int height) : Map<Cell*>(width, height) {}

	~TerrainMap(void)
	{
		for (auto item : _items)
			delete item;
	}

	bool is_walkable(int x, int y) const;
	bool is_explored(int x, int y) const;
};

#endif
