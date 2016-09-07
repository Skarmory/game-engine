#ifndef collision_system_h
#define collision_system_h

#include "system.h"
#include "components.h"
#include "events.h"

class CollisionSystem : public System, public Observer<EntityCreated>
{
	public:
		CollisionSystem(void)  {};
		~CollisionSystem(void) {};

		virtual void update(const EventManager& evm) override;
		void clean(void);
		virtual void receive(const EntityCreated& e) override;
};

#endif
