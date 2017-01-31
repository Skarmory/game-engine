#ifndef light_system_h
#define light_system_h

#include "system.h"
#include "events.h"

class LightSystem : public System, public sov::Observer<EntityCreated>
{
public:
	LightSystem(void) {}

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& event) override;

private:
	const int multipliers[4][8] = {
		{ 1, 0, 0, -1, -1, 0, 0, 1 },
		{ 0, 1, -1, 0, 0, -1, 1, 0 },
		{ 0, 1, 1, 0, 0, -1, -1, 0 },
		{ 1, 0, 0, 1, -1, 0, 0, -1 }
	};

	void cast_light(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy, float dropoff);
};

#endif
