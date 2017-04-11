#ifndef health_component_h
#define health_component_h

#include "component.h"

struct Health : public Component<Health>
{
	explicit Health(int health) : health(health), is_alive(true) {} 

	int health;
	bool is_alive;
};

#endif
