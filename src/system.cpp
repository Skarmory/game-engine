#include "system.h"

System::System(void)
{
}

System::~System(void)
{
}

void System::add_entity(std::shared_ptr<Entity>& entity)
{
	_entities.push_back(entity);
}
