#ifndef time_system_h
#define time_system_h

#include "system.h"
#include "components.h"

class TimeSystem : public System
{
	public:
		virtual	void update(void) override;
		virtual void on_notify(const shared_ptr<Entity>& e, Event evt) override;
};

#endif
