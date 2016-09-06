#ifndef damage_component_h
#define damage_component_h

#include "component.h"

struct Damage : public Component
{
	Damage(int damage) : Component("DamageComponent"), damage(damage) {}

	int damage;
};

#endif
