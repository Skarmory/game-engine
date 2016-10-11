#ifndef light_system_h
#define light_system_h

#include <cstdlib>

#include "system.h"
#include "components.h"
#include "events.h"
#include "level.h"

class LightSystem : public System, public Observer<EntityCreated>
{
	public:
		LightSystem(Level& level) : _level(&level) {}

		virtual void init(EventManager& em) override;
		virtual void update(EventManager& em) override;
		virtual void receive(const EntityCreated& event) override;

	private:
		Level* _level;
};

#endif
