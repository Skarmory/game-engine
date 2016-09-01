#include "render_system.h"

using namespace std;

void RenderSystem::update(void)
{
	clean();	
	
	sort(_entities.begin(), _entities.end(), layer_compare);

	shared_ptr<GraphicComponent>  gfx(nullptr);
	shared_ptr<LocationComponent> loc(nullptr);
	for(vector<weak_ptr<Entity>>::iterator it = _entities.begin(); it != _entities.end(); it++)
	{
		shared_ptr<Entity> e = (*it).lock();

		gfx = e->get_component<GraphicComponent>();
		assert(gfx != nullptr);

		loc = e->get_component<LocationComponent>();
		assert(loc != nullptr);

		if(gfx->fg_colour != TCODColor::black)
		{
			TCODConsole::root->putChar(loc->x, loc->y, gfx->graphic);
			TCODConsole::root->setCharForeground(loc->x, loc->y, gfx->fg_colour);
		}
		
		if(gfx->bg_colour != TCODColor::black)
			TCODConsole::root->setCharBackground(loc->x, loc->y, gfx->bg_colour);
	}
}

void RenderSystem::clean(void)
{
	for(vector<weak_ptr<Entity>>::iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> e = it->lock();

		if(e == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}

		it++;
	}
}

bool RenderSystem::layer_compare(const weak_ptr<Entity>& w1, const weak_ptr<Entity>& w2)
{
	shared_ptr<Entity> s1 = w1.lock();
	shared_ptr<Entity> s2 = w2.lock();

	return s1->get_component<GraphicComponent>()->layer < s2->get_component<GraphicComponent>()->layer;
}

void RenderSystem::on_notify(const shared_ptr<Entity>& entity, Event event)
{
	if(entity->has_component<LocationComponent>() && entity->has_component<GraphicComponent>())
		add_entity(entity);
}
