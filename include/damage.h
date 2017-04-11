#ifndef damage_component_h
#define damage_component_h

#include "component.h"

struct Damage : public Component<Damage>
{
	explicit Damage(int damage) : damage(damage) {}

	int damage;
};

#endif
