#include "render_system.h"

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>

#include "environment.h"
#include "level.h"
#include "colour.h"
#include "location.h"
#include "graphic.h"
#include "light.h"
#include "sprite.h"

void RenderSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);
}

void RenderSystem::update(void)
{
	_clean();	
	
	sort(_entities.begin(), _entities.end(), layer_compare);

	_rtex.create((_viewport.get_width() + 1) * 32, (_viewport.get_height() + 1) * 32);
	_rtex.clear();

	_map_base_terrain();
	_map_drawable_entities();

	_rtex.display();

	_viewport.draw(Sprite(_rtex.getTexture()));
}

void RenderSystem::_map_drawable_entities(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for (entity_iterator it = _entities.begin(); it != _entities.end(); ++it)
	{
		std::shared_ptr<Entity> e = it->lock();

		std::shared_ptr<sov::Graphic>  gfx = e->get_component<sov::Graphic>();
		std::shared_ptr<Location> loc = e->get_component<Location>();
	
		if (loc->z != _level._depth)
			continue;

		pair<int, int> p = _viewport.world_to_screen(loc->x, loc->y);
		if (!_viewport.is_in_bounds(p.first, p.second))
			continue;

		Cell* cell = _level._base_map.get(loc->x, loc->y);

		bool lit     = cell->_light_value > 0.0f;
		bool visible = cell->_visible;

		if (lit && visible)
		{
			Color c = Color::White;
			set_hsv(c, get_hue(c), get_saturation(c) * cell->_light_value, get_value(c) * cell->_light_value);
			gfx->sprite.setColor(c);

			gfx->sprite.setPosition(p.first * SPRITE_WIDTH, p.second * SPRITE_HEIGHT);
			
			_rtex.draw(gfx->sprite, gfx->sprite_transform);
		}
	}
}

void RenderSystem::_map_base_terrain(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for(int y = 0; y < _level._base_map.height(); y++)
	for (int x = 0; x < _level._base_map.width(); x++)
	{
		
		pair<int, int> p = _viewport.world_to_screen(x, y);
		if (p.first < 0 || p.first > _viewport.get_width() + 1 || p.second < 0 || p.second > _viewport.get_height() + 1)
			continue;

		sov::Graphic& gfx = _level._base_map.get(x, y)->_graphic;

		float light_value = _level._base_map.get(x, y)->get_light_value();
		bool lit = light_value > 0.0f;

		bool visible = _level._base_map.get(x, y)->is_visible();
		bool explored = _level.get_cell(x, y).is_explored();
		
		// Do the correct lighting depending on if the cell is lit, shrouded, or in FoW
		if (lit && visible)
		{
			_level._base_map.get(x, y)->_explored = true;
		}
		else if (explored)
		{
			light_value = MIN_LIGHT_PERCENT;
		}
		else
		{
			light_value = 0.05f;
		}
		
		Color c = Color::White;
		set_hsv(c, get_hue(c), get_saturation(c) * light_value, get_value(c) * light_value);
		gfx.sprite.setColor(c);

		gfx.sprite.setPosition(p.first * SPRITE_WIDTH, p.second * SPRITE_HEIGHT);
		
		_rtex.draw(gfx.sprite);
	}
}

void RenderSystem::_clean(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();
	
	for(entity_iterator it = _entities.begin(); it != _entities.end();)
	{
		std::shared_ptr<Entity> e = it->lock();

		if(e == nullptr)
		{
			it = _entities.erase(it);
			continue;
		}

		++it;
	}
}

bool RenderSystem::layer_compare(const weak_ptr<Entity>& w1, const weak_ptr<Entity>& w2)
{
	std::shared_ptr<Entity> s1 = w1.lock();
	std::shared_ptr<Entity> s2 = w2.lock();

	return s1->get_component<sov::Graphic>()->layer < s2->get_component<sov::Graphic>()->layer;
}

void RenderSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<Location>() && event.entity->has_component<sov::Graphic>())
		add_entity(event.entity);
}