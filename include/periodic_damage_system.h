#ifndef periodic_damage_system_h
#define periodic_damage_system_h

#include "system.h"
#include "events.h"

class PeriodicDamageUpdateSystem : public System, public sov::Observer<EntityCreated>
{
public:
	explicit PeriodicDamageUpdateSystem(void) {}

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& entity) override;
};

#endif
