#include "render_system.h"

void RenderSystem::update(void)
{
	std::shared_ptr<GraphicComponent> gfx(nullptr);
	std::shared_ptr<LocationComponent> loc(nullptr);
	for(std::vector<std::weak_ptr<Entity>>::iterator it = _entities.begin(); it != _entities.end();)
	{
		std::shared_ptr<Entity> e = (*it).lock();
		
		if(e != nullptr)
		{
			gfx = e->get_component<GraphicComponent>();
			assert(gfx != nullptr);

			loc = e->get_component<LocationComponent>();
			assert(loc != nullptr);

			TCODConsole::root->putChar(loc->x, loc->y, gfx->graphic);
			TCODConsole::root->setCharForeground(loc->x, loc->y, gfx->colour);
			it++;
		}
		else
		{
			it = _entities.erase(it);
		}
	}
}
