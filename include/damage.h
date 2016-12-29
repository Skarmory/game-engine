#ifndef damage_component_h
#define damage_component_h

#include "component.h"

struct Damage : public Component<Damage>
{
	Damage(int damage) : damage(damage) {}

	int damage;
};

struct PeriodicDamage : Damage
{
	PeriodicDamage(int damage, int per_turns) : Damage(damage), per_turns(per_turns), current_turns(0) {}
	/*virtual BaseComponent* clone(void) const override
	{
		return new PeriodicDamage(*this);
	}*/

	int per_turns;
	int current_turns;
};

#endif
