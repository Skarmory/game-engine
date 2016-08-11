#include "render_system.h"

void RenderSystem::update(void)
{
	std::shared_ptr<GraphicComponent> gcomponent(nullptr);
	std::shared_ptr<LocationComponent> lcomponent(nullptr);
	for(std::vector<std::weak_ptr<Entity>>::iterator it = _entities.begin(); it != _entities.end();)
	{
		std::shared_ptr<Entity> e = (*it).lock();
		
		if(e != nullptr)
		{
			gcomponent = e->get_component<GraphicComponent>();
			assert(gcomponent != nullptr);

			lcomponent = e->get_component<LocationComponent>();
			assert(lcomponent != nullptr);

			TCODConsole::root->putChar(lcomponent->x, lcomponent->y, gcomponent->graphic);

			it++;
		}
		else
		{
			it = _entities.erase(it);
		}
	}
}
