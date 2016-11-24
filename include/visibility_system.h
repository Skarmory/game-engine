#ifndef visibility_system_h
#define visibility_system_h

#include "system.h"
#include "events.h"
#include "level.h"

#include "sight.h"

class VisibilitySystem : public System
{
public:
	VisibilitySystem(const SystemManager& sm, const EntityManager& em, Level* level) : System(sm), _entity_manager(em), _level(level) {}

	virtual void init(sov::EventManager& em) override;
	virtual void update(sov::EventManager& em) override;

	//const vector<bool>& get_visibility_map(void) const;
	
private:
	Level* _level;
	const EntityManager& _entity_manager;

	const int multipliers[4][8] = {
		{ 1, 0, 0, -1, -1, 0, 0, 1 },
		{ 0, 1, -1, 0, 0, -1, 1, 0 },
		{ 0, 1, 1, 0, 0, -1, -1, 0 },
		{ 1, 0, 0, 1, -1, 0, 0, -1 }
	};

	void calculate_fov(int x, int y, int radius, int row, double start_slope, double end_slope, int xx, int xy, int yx, int yy);
};

#endif
