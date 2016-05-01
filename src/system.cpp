#include "system.h"

System::System(void)
{
}

System::~System(void)
{
}

void System::add_entity(Entity* entity)
{
	_entities.push_back(entity);
}
