#ifndef collision_system_h
#define collision_system_h

#include "system.h"
#include "events.h"

class CollisionSystem : public System, public sov::Observer<EntityCreated>
{
public:
	explicit CollisionSystem(void) {};

	virtual void init(void)   override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& e) override;

private:
	void _clean(void);
};

#endif
