#ifndef room_h
#define room_h

typedef struct Dimensions {
	int x, y, w, h;
} Dimensions;

class Room 
{
public:
	Room(void);
	Room(int x, int y, int w, int h);
	Room(Dimensions& d);
	~Room(void);
	
	inline const Dimensions& get_dimensions(void) const { return _dimensions; }
	inline bool is_corner(int x, int y) const {
		return ((x == _dimensions.x || x == _dimensions.x + _dimensions.w - 1) &&
				(y == _dimensions.y || y == _dimensions.y + _dimensions.h - 1));	
	}

	static const char WALL_VERTICAL   = '|';
	static const char WALL_HORIZONTAL = '-'; 
	static const char WALL_CORNER     = '-';
	static const char ROOM_FLOOR	  = '.';

private:
	Dimensions _dimensions;
};

#endif
