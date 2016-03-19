#ifndef room_h
#define room_h

typedef struct Dimensions {
	int x, y, width, height;
} Dimensions;

class Room 
{
public:
	Room(void);
	Room(int x, int y, int width, int height);
	Room(Dimensions& d);
	~Room(void);
	
	inline const Dimensions& getDimensions(void) const { return _dimensions; }
	inline bool isCorner(int x, int y) const {
		return ((x == _dimensions.x || x == _dimensions.x + _dimensions.width - 1) &&
				(y == _dimensions.y || y == _dimensions.y + _dimensions.height - 1));	
	}

	static const char WALL_VERTICAL   = '|';
	static const char WALL_HORIZONTAL = '-'; 
	static const char WALL_CORNER     = '-';
	static const char ROOM_FLOOR	  = '.';

private:
	Dimensions _dimensions;
};

#endif
