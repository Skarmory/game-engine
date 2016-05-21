#ifndef cell_h
#define cell_h

class Cell {
public:
	Cell(void);
	Cell(char, bool);
	~Cell(void);

	char get_display(void) const;
	void display(char);
	bool is_walkable(void) const;

private:
	char _display;
	bool _walkable;
};

#endif
