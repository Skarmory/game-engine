#ifndef collision_system_h
#define collision_system_h

#include "system.h"
#include "location_component.h"
#include "collision_component.h"
#include "collided_component.h"

class CollisionSystem : public System, public Observable
{
	public:
		CollisionSystem(void)  {};
		~CollisionSystem(void) {};

		virtual void update(void) override;
		virtual void on_notify(const shared_ptr<Entity>&, Event) override;
};

#endif
