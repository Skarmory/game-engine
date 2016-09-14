#ifndef timed_health_system_h
#define timed_health_system_h

#include "system.h"
#include "events.h"
#include "components.h"

class TimedHealthSystem : public System, public Observer<EntityCreated>
{
	public:
		virtual void init(EventManager& evm) override;
		virtual void update(EventManager& evm) override;
		virtual void receive(const EntityCreated& event) override;
};

#endif
