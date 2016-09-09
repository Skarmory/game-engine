#ifndef time_system_h
#define time_system_h

#include "system.h"
#include "components.h"
#include "events.h"

class TimeSystem : public System, Observer<EntityCreated>
{
	public:
		virtual	void update(const EventManager& evm) override;
		virtual void receive(const EntityCreated& event) override;
};

#endif
