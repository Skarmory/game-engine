#ifndef health_component_h
#define health_component_h

#include "component.h"

struct HealthComponent : public Component
{
	HealthComponent(int health) : Component("HealthComponent"), health(health) {} 
	int health;
};

#endif
