#include "light_system.h"

#include <cstdlib>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "environment.h"
#include "light.h"
#include "location.h"
#include "level.h"
#include "render_system.h"
#include "graphics.h"

void LightSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);

	// Temporary
	_light_texture.create(80.0f * 32.0f, 80.f * 32.0f);
	_light_shader.loadFromMemory(_light_vshader_src, _light_fshader_src);
	
	_light_shader.setUniform("colour", sf::Glsl::Vec4(sf::Color::White));
	_light_shader.setUniform("window_height", 80.0f * 32.0f);
}

void LightSystem::update(void)
{
	_light_texture.clear();

	for (auto it = _entities.begin(); it != _entities.end(); ++it)
	{
		LightSource* light = (*it)->get_component<LightSource>();
		sov::Graphics* gfx = (*it)->get_component<sov::Graphics>();

		sf::CircleShape circle;
		sf::Vector2f pos = gfx->sprite.getPosition();
		pos.x += 16.0f;
		pos.y += 16.0f;
		circle.setPosition(pos);
		circle.setRadius(light->radius * 32.0f);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOrigin(circle.getRadius(), circle.getRadius());

		_light_shader.setUniform("centre", pos);
		_light_shader.setUniform("radius", circle.getRadius());

		_light_texture.draw(circle, &_light_shader);
	}

	_light_texture.display();
}


const sf::RenderTexture& LightSystem::get_lightmap(void) const
{
	return _light_texture;
}

void LightSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<LightSource>())
		_entities.push_back(event.entity);
}
