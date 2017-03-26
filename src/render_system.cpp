#include "render_system.h"

#include <algorithm>
#include <vector>

#include "environment.h"
#include "level.h"
#include "colour.h"
#include "location.h"
#include "graphic.h"
#include "light.h"

#include <iostream>

using namespace std;
using namespace sov;

void RenderSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);
}

void RenderSystem::update(void)
{
	clean();	
	
	sort(_entities.begin(), _entities.end(), layer_compare);

	map_base_terrain();
	map_drawable_entities();
}

void RenderSystem::map_drawable_entities(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for (entity_iterator it = _entities.begin(); it != _entities.end(); ++it)
	{
		shared_ptr<Entity> e = it->lock();

		shared_ptr<Graphic>  gfx = e->get_component<Graphic>();
		shared_ptr<Location> loc = e->get_component<Location>();

		//int id = e->get_id();
		//if (id == 0) {
		//	std::cout << "x=" << loc->x << " y=" << loc->y << std::endl;  
		//}
	
		if (loc->z != _level._depth)
			continue;

		pair<float, float> p = _camera.world_to_screen(loc->x, loc->y);
		if (!_camera.is_in_bounds(p.first, p.second))
			continue;

		RenderItem r = {*gfx, *loc};
		_render_entities.push_back(r);

		//sov::Glyph& glyph = _composed_map.get(p.first, p.second);
		// sov::Glyp& glyph = r.graphic.glyph;

		// Cell*& cell = _level._base_map.get(loc->x, loc->y);

		// bool lit     = cell->_light_value > 0.0f;
		// bool visible = cell->_visible;

		// if (lit && visible)
		// {
		// 	if (gfx->glyph.fg_colour != sf::Color::Transparent)
		// 	{
		// 		HSV hsv = get_hsv(gfx->glyph.fg_colour);
		// 		hsv.hue *= cell->_light_value;
		// 		hsv.saturation *= cell->_light_value;
		// 		hsv.value *= cell->_light_value;

		// 		set_hsv(glyph.fg_colour, hsv.hue, hsv.saturation, hsv.value);
		// 		glyph.glyph = gfx->glyph.glyph;
		// 	}

		// 	if (gfx->glyph.bg_colour != sf::Color::Transparent)
		// 	{
		// 		HSV hsv = get_hsv(gfx->glyph.bg_colour);
		// 		hsv.saturation *= cell->_light_value;
		// 		hsv.value *= cell->_light_value;

		// 		set_hsv(glyph.bg_colour, hsv.hue, hsv.saturation, hsv.value);
		// 	}
		// }
	}
}

void RenderSystem::map_base_terrain(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for (int x = 0; x < _camera.get_width(); x++)
	for (int y = 0; y < _camera.get_height(); y++)
	{
		sov::Glyph& glyph = _composed_map.get(x, y);
		
		pair<int, int> p = _camera.screen_to_world(x, y);
		if (!_level.is_in_bounds(p.first, p.second))
			continue;

		const sov::Glyph& base = _level._base_map.get(p.first, p.second)->get_glyph();
		float light_value = _level._base_map.get(p.first, p.second)->get_light_value();
		bool lit = light_value > 0.0f;

		glyph.glyph = base.glyph;
		bool visible = _level._base_map.get(p.first, p.second)->is_visible();
		bool explored = _level.get_cell(p.first, p.second).is_explored();
		
		// Do the correct lighting depending on if the cell is lit, shrouded, or in FoW
		if (lit && visible)
		{
			set_hsv(glyph.fg_colour, get_hue(base.fg_colour), get_saturation(base.fg_colour) * light_value, get_value(base.fg_colour) * light_value);
			set_hsv(glyph.bg_colour, get_hue(base.bg_colour), get_saturation(base.bg_colour) * light_value, get_value(base.bg_colour) * light_value);

			_level._base_map.get(p.first, p.second)->_explored = true;
		}
		else if (explored)
		{
			set_hsv(glyph.fg_colour, get_hue(base.fg_colour), get_saturation(base.fg_colour) * MIN_LIGHT_PERCENT, get_value(base.fg_colour) * MIN_LIGHT_PERCENT);
			set_hsv(glyph.bg_colour, get_hue(base.bg_colour), get_saturation(base.bg_colour) * MIN_LIGHT_PERCENT, get_value(base.bg_colour) * MIN_LIGHT_PERCENT);
		}
		else
		{
			set_hsv(glyph.fg_colour, get_hue(base.fg_colour), 0.0f, 0.0f);
			set_hsv(glyph.bg_colour, get_hue(base.bg_colour), 0.0f, 0.0f);
		}
	}
}

void RenderSystem::clean(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	if (_composed_map.size() == 0)
		_composed_map = Map<sov::Glyph>(_level.get_map_width(), _level.get_map_height());
	
	for(entity_iterator it = _entities.begin(); it != _entities.end();)
	{
		shared_ptr<Entity> e = it->lock();

		if(e == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}

		++it;
	}

	_render_entities.clear();
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

const Map<sov::Glyph>& RenderSystem::get_composed_map(void) const
{
	return _composed_map;
}

const std::vector<sov::RenderItem>& RenderSystem::get_render_items(void) const
{
	return _render_entities;
}
