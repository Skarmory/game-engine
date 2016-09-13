#ifndef health_component_h
#define health_component_h

#include "component.h"

struct Health : public Component
{
	Health(int health) : health(health) {} 
	int health;
};

struct TimedHealth : public Component
{
	TimedHealth(int turns) : turns(turns), remaining(turns) {} 
	const int turns;
	int remaining;
};

#endif
