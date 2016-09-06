#ifndef collision_system_h
#define collision_system_h

#include "system.h"
#include "components.h"

class CollisionSystem : public System, public Observable
{
	public:
		CollisionSystem(void)  {};
		~CollisionSystem(void) {};

		virtual void update(void) override;
		void clean(void);
		virtual void on_notify(const shared_ptr<Entity>&, Event) override;
};

#endif
