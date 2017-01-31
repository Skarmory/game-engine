#ifndef visibility_system_h
#define visibility_system_h

#include "system.h"
#include "events.h"


class VisibilitySystem : public System
{
public:
	VisibilitySystem(void) {}

	virtual void init(void) override;
	virtual void update(void) override;
	
private:
	const int multipliers[4][8] = {
		{ 1, 0, 0, -1, -1, 0, 0, 1 },
		{ 0, 1, -1, 0, 0, -1, 1, 0 },
		{ 0, 1, 1, 0, 0, -1, -1, 0 },
		{ 1, 0, 0, 1, -1, 0, 0, -1 }
	};

	void calculate_fov(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy);
};

#endif
