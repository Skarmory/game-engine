#ifndef timed_health_system_h
#define timed_health_system_h

#include "system.h"
#include "events.h"

class TimedHealthSystem : public System, public sov::Observer<EntityCreated>
{
public:
	explicit TimedHealthSystem(void) {}

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& event) override;
};

#endif
