#ifndef events_h
#define events_h

#include "entity.h"
#include "event.h"
#include "level_transition.h"
#include "level.h"

struct EntityCreated : sov::Event
{
	explicit EntityCreated(const std::shared_ptr<Entity>& entity) : entity(entity) {}
	std::shared_ptr<Entity> entity;
};

struct CollisionEvent : sov::Event
{
	explicit CollisionEvent(const std::shared_ptr<Entity>& e1, const std::shared_ptr<Entity>& e2) : e1(e1), e2(e2) {}
	std::shared_ptr<Entity> e1;
	std::shared_ptr<Entity> e2;
};

struct LevelTransitionEvent : sov::Event
{
	explicit LevelTransitionEvent(const std::shared_ptr<LevelTransition>& transition) : level_transition(transition) {}
	std::shared_ptr<LevelTransition> level_transition;
};

struct MoveEvent : sov::Event
{
	explicit MoveEvent(const std::shared_ptr<Entity>& entity) : entity(entity) {}
	std::shared_ptr<Entity> entity;
};

#endif
