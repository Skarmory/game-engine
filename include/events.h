#ifndef events_h
#define events_h

#include "entity.h"
#include "event.h"
#include "level_transition.h"
#include "level.h"

struct EntityCreated : sov::Event
{
	explicit EntityCreated(Entity* entity) : entity(entity) {}
	Entity* entity;
};

struct EntityDestroyed : sov::Event
{
	explicit EntityDestroyed(Entity* entity) : entity(entity) {}
	Entity* entity;
};

struct CollisionEvent : sov::Event
{
	explicit CollisionEvent(Entity* entity1, Entity* entity2) : e1(entity1), e2(entity2) {}
	Entity* e1;
	Entity* e2;
};

struct LevelTransitionEvent : sov::Event
{
	explicit LevelTransitionEvent(LevelTransition* transition) : level_transition(transition) {}
	LevelTransition* level_transition;
};

struct MoveEvent : sov::Event
{
	explicit MoveEvent(Entity* entity) : entity(entity) {}
	Entity* entity;
};

#endif
