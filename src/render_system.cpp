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

	map_terrain();
	map_drawable_entities();
	map_lighting();
}

void RenderSystem::map_terrain(void)
{
	int mw = _level->get_map_width();
	int mh = _level->get_map_height();

	for (int x = 0; x < mw; x++)
	for (int y = 0; y < mh; y++)
	{
		_composed_map.set(x, y, _level->get_cell(x, y).get_glyph());
	}
}

void RenderSystem::map_drawable_entities(void)
{
	for (entity_iterator it = _entities.begin(); it != _entities.end(); it++)
	{
		shared_ptr<Entity> e = it->lock();

		shared_ptr<Graphic>  gfx = e->get_component<Graphic>();
		shared_ptr<Location> loc = e->get_component<Location>();
	
		Glyph& glyph = _composed_map.get(loc->x, loc->y);

		if (gfx->glyph.fg_colour != sf::Color::Transparent)
		{
			glyph.fg_colour = gfx->glyph.fg_colour;
			glyph.glyph = gfx->glyph.glyph;
		}

		if (gfx->glyph.bg_colour != sf::Color::Transparent)
		{			
			glyph.bg_colour = gfx->glyph.bg_colour;
		}		
	}
}

void RenderSystem::map_lighting(void)
{
	int mw = _level->get_map_width();
	int mh = _level->get_map_height();

	for (int x = 0; x < mw; x++)
	for (int y = 0; y < mh; y++)
	{
		Glyph& glyph = _composed_map.get(x, y);
		
		float light_value = _level->_light_map.get(x, y);
		bool lit = light_value > 0.0f;

		bool visible = _level->_vision_map.get(x, y);
		bool explored = _level->get_cell(x, y).is_explored();
		
		// Do the correct lighting depending on if the cell is lit, shrouded, or in FoW
		if (lit && visible)
		{
			set_hsv(glyph.fg_colour, get_hue(glyph.fg_colour), get_saturation(glyph.fg_colour) * light_value, get_value(glyph.fg_colour) * light_value);
			set_hsv(glyph.bg_colour, get_hue(glyph.bg_colour), get_saturation(glyph.bg_colour) * light_value, get_value(glyph.bg_colour) * light_value);

			_level->_base_map.get(x, y)->_explored = true;
		}
		else if (explored)
		{
			set_hsv(glyph.fg_colour, get_hue(glyph.fg_colour), get_saturation(glyph.fg_colour) * MIN_LIGHT_PERCENT, get_value(glyph.fg_colour) * MIN_LIGHT_PERCENT);
			set_hsv(glyph.bg_colour, get_hue(glyph.bg_colour), get_saturation(glyph.bg_colour) * MIN_LIGHT_PERCENT, get_value(glyph.bg_colour) * MIN_LIGHT_PERCENT);
		}
		else
		{
			set_hsv(glyph.fg_colour, get_hue(glyph.fg_colour), 0.0f, 0.0f);
			set_hsv(glyph.bg_colour, get_hue(glyph.bg_colour), 0.0f, 0.0f);
		}
	}
}

void RenderSystem::clean(void)
{
	if (_composed_map.size() == 0)
		_composed_map = Map<Glyph>(_level->get_map_width(), _level->get_map_height());
	
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

const Map<Glyph>& RenderSystem::get_composed_map(void) const
{
	return _composed_map;
}
