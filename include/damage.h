#ifndef damage_component_h
#define damage_component_h

#include "component.h"

struct Damage : public Component
{
	Damage(int damage) : damage(damage) {}

	int damage;
};

struct PeriodicDamage : public Damage
{
	PeriodicDamage(int damage, int per_turns) : Damage(damage), per_turns(per_turns) {}

	int per_turns;
	int current_turns;
};

#endif
