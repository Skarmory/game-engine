#ifndef health_component_h
#define health_component_h

#include "component.h"

struct Health : public Component<Health>
{
	explicit Health(int health) : health(health), is_alive(true) {} 

	int health;
	bool is_alive;
};

struct TimedHealth : public Component<TimedHealth>
{
	explicit TimedHealth(int turns) : turns(turns), remaining(turns) {} 

	const int turns;
	int remaining;
};

#endif
