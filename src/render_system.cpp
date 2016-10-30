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

	for(entity_iterator it = _entities.begin(); it != _entities.end(); it++)
	{
		shared_ptr<Entity> e = it->lock();

		shared_ptr<Graphic>  gfx = e->get_component<Graphic>();
		shared_ptr<Location> loc = e->get_component<Location>();

		if (_level->is_visible(loc->x, loc->y))
		{
			//pair<int, int> sxy = _window.world_to_screen(loc->x, loc->y);

			Cell& cell = _level->_map.get(loc->x, loc->y);

			// Black is the "null" value, i.e. there should be no colour here, so things can be layered "dynamically"
			if (gfx->glyph.fg_colour != TCODColor::black)
			{
				TCODColor fg = gfx->glyph.fg_colour;

				cell._glyph.fg_colour.setHSV(fg.getHue(), fg.getSaturation() * cell._light_value, fg.getValue() * cell._light_value);
				cell._glyph.glyph = gfx->glyph.glyph;

				//fg.setHSV(fg.getHue(), fg.getSaturation() * _level.get_cell_light(loc->x, loc->y), fg.getValue() * _level.get_cell_light(loc->x, loc->y));

				//TCODConsole::root->putChar(sxy.first, sxy.second, gfx->glyph.glyph);
				//TCODConsole::root->setCharForeground(sxy.first, sxy.second, fg);
			}

			if (gfx->glyph.bg_colour != TCODColor::black)
			{
				TCODColor bg = gfx->glyph.bg_colour;
				cell._glyph.bg_colour.setHSV(bg.getHue(), bg.getSaturation() * cell._light_value, bg.getValue() * cell._light_value);
				//TCODConsole::root->setCharBackground(sxy.first, sxy.second, bg);
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
