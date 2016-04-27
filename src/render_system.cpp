#include "render_system.h"

RenderSystem::RenderSystem(void)
{

}

RenderSystem::~RenderSystem(void)
{
}

void RenderSystem::update(void)
{
	const GraphicComponent* gcomponent;
	const LocationComponent* lcomponent;
	for(std::vector<Entity*>::iterator it = _entities.begin(); it != _entities.end(); it++)
	{
		gcomponent = dynamic_cast<const GraphicComponent*>((*it)->get_component("GraphicComponent"));
		assert(gcomponent != nullptr);

		lcomponent = dynamic_cast<const LocationComponent*>((*it)->get_component("LocationComponent"));
		assert(lcomponent != nullptr);

		mvaddch(lcomponent->y(), lcomponent->x(), gcomponent->graphic());
	}
}
