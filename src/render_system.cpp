#include "render_system.h"

using namespace std;

void RenderSystem::init(EventManager& evm)
{
	evm.subscribe<EntityCreated>(*this);
}

void RenderSystem::update(EventManager& evm)
{
	clean();	
	
	sort(_entities.begin(), _entities.end(), layer_compare);

	shared_ptr<Graphic>  gfx(nullptr);
	shared_ptr<Location> loc(nullptr);
	for(entity_iterator it = _entities.begin(); it != _entities.end(); it++)
	{
		shared_ptr<Entity> e = it->lock();

		gfx = e->get_component<Graphic>();
		assert(gfx != nullptr);

		loc = e->get_component<Location>();
		assert(loc != nullptr);

		if (_level->is_visible(loc->x, loc->y))
		{
			// Black is the "null" value, i.e. there should be no colour here, so things can be layered "dynamically"
			if (gfx->fg_colour != TCODColor::black)
			{
				TCODColor fg = gfx->fg_colour;
				fg.setHSV(fg.getHue(), fg.getSaturation() * _level->get_cell_light(loc->x, loc->y), fg.getValue() * _level->get_cell_light(loc->x, loc->y));

				TCODConsole::root->putChar(loc->x, loc->y, gfx->graphic);
				TCODConsole::root->setCharForeground(loc->x, loc->y, fg);	
			}

			if (gfx->bg_colour != TCODColor::black)
			{
				TCODColor bg = gfx->bg_colour;
				bg.setHSV(bg.getHue(), bg.getSaturation() * _level->get_cell_light(loc->x, loc->y), bg.getValue() * _level->get_cell_light(loc->x, loc->y));
				TCODConsole::root->setCharBackground(loc->x, loc->y, bg);
			}
		}
	}
}

void RenderSystem::clean(void)
{
	for(entity_iterator it = _entities.begin(); it != _entities.end();)
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

	return s1->get_component<Graphic>()->layer < s2->get_component<Graphic>()->layer;
}

void RenderSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<Location>() && event.entity->has_component<Graphic>())
		add_entity(event.entity);
}
