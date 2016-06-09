#ifndef damage_component_h
#define damage_component_h

#include "component.h"

struct DamageComponent : public Component
{
	DamageComponent(int damage) : Component("DamageComponent"), damage(damage) {}
	~DamageComponent(void) {};

	int damage;
};

#endif
