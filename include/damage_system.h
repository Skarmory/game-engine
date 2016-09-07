#ifndef damage_system_h
#define damage_system_h

#include "system.h"
#include "components.h"
#include "events.h"

class DamageSystem : public System, Observer<CollisionEvent>
{
	public:
		DamageSystem(void) {}
		~DamageSystem(void) {}

		virtual void update(const EventManager& evm) override;
		virtual void receive(const CollisionEvent& event) override;

};

#endif
