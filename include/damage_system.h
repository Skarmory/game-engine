#ifndef damage_system_h
#define damage_system_h

#include "system.h"
#include "components.h"

class DamageSystem : public System
{
	public:
		DamageSystem(void) {}
		~DamageSystem(void) {}

		virtual void update(void) override;
		virtual void on_notify(const shared_ptr<Entity>& e, Event evt) override;
};

#endif
