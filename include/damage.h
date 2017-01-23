#ifndef damage_component_h
#define damage_component_h

#include "component.h"

struct Damage : public Component<Damage>
{
	explicit Damage(int damage) : damage(damage) {}

	int damage;
};

struct PeriodicDamage : public Component<PeriodicDamage>
{
	explicit PeriodicDamage(int damage, int per_turns) : damage(damage), per_turns(per_turns), current_turns(0) {}

	int damage;
	int per_turns;
	int current_turns;
};

#endif
