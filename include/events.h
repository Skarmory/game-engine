#ifndef events_h
#define events_h

#include <algorithm>
#include "event.h"

using namespace std;

struct EntityCreated : sov::Event
{
	explicit EntityCreated(const shared_ptr<Entity>& entity) : entity(entity) {}
	shared_ptr<Entity> entity;
};

struct CollisionEvent : sov::Event
{
	CollisionEvent(const shared_ptr<Entity>& e1, const shared_ptr<Entity>& e2) : e1(e1), e2(e2) {}
	shared_ptr<Entity> e1;
	shared_ptr<Entity> e2;
};

#endif
