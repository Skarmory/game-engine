#ifndef light_system_h
#define light_system_h

#include <cstdlib>
#include <algorithm>

#include "system.h"
#include "components.h"
#include "events.h"
#include "level_manager.h"

using namespace sov;

class LightSystem : public System, public Observer<EntityCreated>
{
public:
	LightSystem(const SystemManager& sm, LevelManager& level_manager) : System(sm), _level_manager(level_manager) {}

	virtual void init(EventManager& em) override;
	virtual void update(EventManager& em) override;
	virtual void receive(const EntityCreated& event) override;

private:
	LevelManager& _level_manager;

	const int multipliers[4][8] = {
		{ 1, 0, 0, -1, -1, 0, 0, 1 },
		{ 0, 1, -1, 0, 0, -1, 1, 0 },
		{ 0, 1, 1, 0, 0, -1, -1, 0 },
		{ 1, 0, 0, 1, -1, 0, 0, -1 }
	};

	void cast_light(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy, float dropoff);
};

#endif
