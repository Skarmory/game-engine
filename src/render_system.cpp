#include "render_system.h"

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>

#include "environment.h"
#include "level.h"
#include "colour.h"
#include "location.h"
#include "graphics.h"
#include "light.h"
#include "sprite.h"
#include "light_system.h"

void RenderSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);

	// Temporarily just create a 80x40 cell texture.
	// 80x40 is the largest size for the time being.
	_rtex.create(80 * SPRITE_WIDTH, 40 * SPRITE_HEIGHT);
}

void RenderSystem::update(void)
{	
	sort(_entities.begin(), _entities.end(), layer_compare);

	_rtex.clear();

	_map_base_terrain();
	_map_drawable_entities();

	const sf::RenderTexture& lightmap = Environment::get().get_system_manager()->get<LightSystem>().get_lightmap();

	_rtex.draw(Sprite(lightmap.getTexture()), sf::BlendMultiply);
	_rtex.display();

	_viewport->draw(Sprite(_rtex.getTexture()));
}

void RenderSystem::_map_drawable_entities(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for (auto it = _entities.begin(); it != _entities.end(); ++it)
	{
		sov::Graphics*  gfx = (*it)->get_component<sov::Graphics>();
		Location* loc = (*it)->get_component<Location>();
	
		if (loc->z != _level._depth)
			continue;

		Cell* cell = _level._base_map.get(loc->x, loc->y);

		/*bool lit = true;*/
		bool visible = true;// cell->_visible;

		if (visible)
		{
			Sprite s = gfx->sprite;
			sf::Transform t = sf::Transform::Identity;
			Vector2f sprite_pos = s.getPosition();

			t.translate(sprite_pos.x + 16.0f, sprite_pos.y + 16.0f);
			t.combine(gfx->sprite_transform);
			t.translate(-sprite_pos.x - 16.0f, -sprite_pos.y - 16.0f);

			_rtex.draw(s, t);
		}
	}
}

void RenderSystem::_map_base_terrain(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();

	for (int y = 0; y < _level._base_map.height(); y++)
	for (int x = 0; x < _level._base_map.width(); x++)
	{
		sov::Graphics& gfx = _level._base_map.get(x, y)->_graphic;

		bool visible = _level._base_map.get(x, y)->is_visible();
		bool explored = _level.get_cell(x, y).is_explored();
		
		// Do the correct lighting depending on if the cell is lit, shrouded, or in FoW
		if (visible)
			_level._base_map.get(x, y)->_explored = true;
		
		Sprite s = gfx.sprite;
		
		sf::Transform t = sf::Transform::Identity;
		t.translate(x * SPRITE_WIDTH + 16.0f, y * SPRITE_HEIGHT + 16.0f);
		t.combine(gfx.sprite_transform);
		t.translate(-16.0f, -16.0f);
		
		_rtex.draw(s, t);
	}
}

bool RenderSystem::layer_compare(Entity* e1, Entity* e2)
{
	return e1->get_component<sov::Graphics>()->layer < e2->get_component<sov::Graphics>()->layer;
}

void RenderSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<Location>() && event.entity->has_component<sov::Graphics>())
		_entities.push_back(event.entity);
}