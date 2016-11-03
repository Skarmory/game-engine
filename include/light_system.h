#ifndef light_system_h
#define light_system_h

#include <cstdlib>
#include <algorithm>

#include "system.h"
#include "components.h"
#include "events.h"
#include "level.h"

class LightSystem : public System, public Observer<EntityCreated>
{
	public:
		LightSystem(const SystemManager& sm, Level* level) : System(sm), _level(level) {}

		virtual void init(EventManager& em) override;
		virtual void update(EventManager& em) override;
		virtual void receive(const EntityCreated& event) override;

	private:
		Level* _level;

		const int multipliers[4][8] = {
			{ 1, 0, 0, -1, -1, 0, 0, 1 },
			{ 0, 1, -1, 0, 0, -1, 1, 0 },
			{ 0, 1, 1, 0, 0, -1, -1, 0 },
			{ 1, 0, 0, 1, -1, 0, 0, -1 }
		};

		void cast_light(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy, float dropoff);
};

#endif
