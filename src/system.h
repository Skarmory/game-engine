#ifndef system_h
#define system_h

#include <vector>
#include "entity.h"

class System {
public:
	System(void);
	virtual ~System(void);

	virtual void update(void) = 0;
	virtual void add_entity(Entity* entity);

protected:
	std::vector<Entity*> _entities;
};

#endif
