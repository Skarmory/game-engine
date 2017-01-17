#ifndef events_h
#define events_h

#include <algorithm>
#include "event.h"
#include "components.h"

using namespace std;

struct EntityCreated : sov::Event
{
	explicit EntityCreated(const shared_ptr<Entity>& entity) : entity(entity) {}
	shared_ptr<Entity> entity;
};

struct CollisionEvent : sov::Event
{
	explicit CollisionEvent(const shared_ptr<Entity>& e1, const shared_ptr<Entity>& e2) : e1(e1), e2(e2) {}
	shared_ptr<Entity> e1;
	shared_ptr<Entity> e2;
};

struct LevelTransitionEvent : sov::Event
{
	explicit LevelTransitionEvent(const shared_ptr<LevelTransition>& transition) : level_transition(transition) {}
	shared_ptr<LevelTransition> level_transition;
};

#endif
