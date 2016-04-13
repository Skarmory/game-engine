#ifndef cell_h
#define cell_h

class Cell {
public:
	Cell(void);
	Cell(char display);
	~Cell(void);

	char get_display(void) const;
	void display(char c);

private:
	char _display;
};

#endif
