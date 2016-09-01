#ifndef system_h
#define system_h

#include <vector>
#include <memory>

#include "entity.h"
#include "observer.h"

class System : public Observer {
public:
	System(void) {};
	virtual ~System(void) {};

	virtual void update(void) = 0;
	
	virtual void add_entity(const std::shared_ptr<Entity>& entity)
	{
		_entities.push_back(entity);
	}

protected:
	std::vector<std::weak_ptr<Entity>> _entities;
};

#endif
