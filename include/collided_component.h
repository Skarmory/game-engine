#ifndef collided_component_h
#define collided_component_h

#include "component.h"
#include "entity.h"

using namespace std;

struct CollidedComponent : public Component
{
	CollidedComponent(const shared_ptr<Entity>& collided) : Component("CollidedComponent") 
	{
		collided_with.push_back(collided);
	}

	vector<shared_ptr<Entity>> collided_with;
};

#endif
