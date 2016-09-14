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

		virtual void init(EventManager& evm)   override;
		virtual void update(EventManager& evm) override;
		virtual void receive(const EntityCreated& e) override;

	private:
		void clean(void);
};

#endif
