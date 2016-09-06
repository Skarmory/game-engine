#ifndef health_component_h
#define health_component_h

#include "component.h"

struct Health : public Component
{
	Health(int health) : Component("HealthComponent"), health(health) {} 
	int health;
};

#endif
