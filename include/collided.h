#ifndef collided_component_h
#define collided_component_h

#include "component.h"
#include "entity.h"

using namespace std;

struct Collided : public Component<Collided>
{
	explicit Collided(Entity* collided) 
	{
		collided_with.push_back(collided);
	}

	std::vector<Entity*> collided_with;
};

#endif
