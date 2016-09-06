#ifndef timed_life_component_h
#define timed_life_component_h

#include "component.h"

struct TimedLife : public Component
{
	TimedLife(int lifetime) : Component("TimedLifeComponent"), lifetime(lifetime), expires_in(lifetime), turns_passed(0) {}

	const int lifetime;
	int expires_in;
	int turns_passed;
};

#endif
