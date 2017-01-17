#ifndef visibility_system_h
#define visibility_system_h

#include "system.h"
#include "events.h"
#include "components.h"
#include "level_manager.h"
#include "entity_manager.h"

class VisibilitySystem : public System
{
public:
	VisibilitySystem(const SystemManager& sm, const EntityManager& em, LevelManager& level_manager) : System(sm), _entity_manager(em), _level_manager(level_manager) {}

	virtual void init(sov::EventManager& em) override;
	virtual void update(sov::EventManager& em) override;
	
private:
	LevelManager& _level_manager;
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
