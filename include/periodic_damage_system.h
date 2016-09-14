#ifndef periodic_damage_system_h
#define periodic_damage_system_h

#include "system.h"
#include "events.h"
#include "components.h"

class PeriodicDamageUpdateSystem : public System, public Observer<EntityCreated>
{
	public:
		virtual void init(EventManager& evm) override;
		virtual void update(EventManager& evm) override;
		virtual void receive(const EntityCreated& entity) override;
};

#endif
