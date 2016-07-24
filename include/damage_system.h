#ifndef damage_system_h
#define damage_system_h

#include "system.h"
#include "collided_component.h"
#include "health_component.h"
#include "damage_component.h"

class DamageSystem : public System
{
	public:
		DamageSystem(void) {}
		~DamageSystem(void) {}

		virtual void update(void) override;
};

#endif
