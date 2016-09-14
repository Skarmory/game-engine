#ifndef damage_system_h
#define damage_system_h

#include "system.h"
#include "components.h"
#include "events.h"

class DamageSystem : public System, public Observer<CollisionEvent>
{
	public:
		DamageSystem(void) {}
		~DamageSystem(void) {}
		
		virtual void init(EventManager& evm) override;
		virtual void update(EventManager& evm) override;
		virtual void receive(const CollisionEvent& event) override;

};

#endif
