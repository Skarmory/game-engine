#ifndef timed_health_system_h
#define timed_health_system_h

#include "system.h"
#include "events.h"
#include "components.h"

using namespace sov;

class TimedHealthSystem : public System, public Observer<EntityCreated>
{
public:
	TimedHealthSystem(const SystemManager& sm) : System(sm) {}

	virtual void init(EventManager& evm) override;
	virtual void update(EventManager& evm) override;
	virtual void receive(const EntityCreated& event) override;
};

#endif
