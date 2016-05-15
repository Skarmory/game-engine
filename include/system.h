#ifndef system_h
#define system_h

#include <vector>
#include <memory>
#include "entity.h"

class System {
public:
	System(void);
	virtual ~System(void);

	virtual void update(void) = 0;
	virtual void add_entity(std::shared_ptr<Entity>&);

protected:
	std::vector<std::weak_ptr<Entity>> _entities;
};

#endif
