#ifndef damage_system_h
#define damage_system_h

#include "system.h"
#include "events.h"

class DamageSystem : public System, public sov::Observer<CollisionEvent>
{
public:
	explicit DamageSystem(void) {}
		
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const CollisionEvent& event) override;
};

#endif
