#include "light_system.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <cmath>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "util.h"
#include "sov_math.h"
#include "environment.h"
#include "light.h"
#include "location.h"
#include "level.h"
#include "render_system.h"
#include "graphics.h"

void LightSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);

	// Temporary hardcoding for testing map
	float width = 80.f * 32.f;
	float height = 40.f * 32.f;

	_light_map.create(width, height);
	_occlusion_map.create(width, height);

	_light_shader.loadFromFile(_shader_path + "generic.vs", _shader_path + "light.frag");
	_light_shader.setUniform("colour", sf::Glsl::Vec4(sf::Color::White));
	_light_shader.setUniform("width", width);
	_light_shader.setUniform("height", height);
}

void LightSystem::update(void)
{
	const Level& level = Environment::get().get_level_manager()->get_current();
	_light_map.clear(sf::Color::Black);

	for (auto& it = _entities.begin(); it != _entities.end(); ++it)
	{
		_occlusion_map.clear(sf::Color::Transparent);

		LightSource* light = (*it)->get_component<LightSource>();
		sov::Graphics* gfx = (*it)->get_component<sov::Graphics>();
		sf::VertexArray varr(sf::Triangles);
		std::vector<sf::Vector2f> light_geom;

		sf::Vector2f light_centre = gfx->sprite.getPosition() + sf::Vector2f(16.f, 16.f);

		// Block lighting based on light occluders within the level
		for(auto& occ : level._occluders)
		{
			sf::Vector2f occluder_centre(occ->_x * 32.f + 16.f, occ->_y * 32.f + 16.f);

			// Corners of the square that the occluder occupies
			sf::Vector2f top_left     = occluder_centre + sf::Vector2f(-16.f, -16.f);
			sf::Vector2f top_right    = occluder_centre + sf::Vector2f(16.f, -16.f);
			sf::Vector2f bottom_left  = occluder_centre + sf::Vector2f(-16.f, 16.f);
			sf::Vector2f bottom_right = occluder_centre + sf::Vector2f( 16.f, 16.f);

			// Get ray to each corner of the occluder from light centre
			std::vector<sf::Vector2f> rays;
			rays.push_back(top_left - light_centre);
			rays.push_back(top_right - light_centre);
			rays.push_back(bottom_left - light_centre);
			rays.push_back(bottom_right - light_centre);

			// For each ray, find out whether it intersects anything
			for (auto& ray = rays.begin(); ray != rays.end(); ++ray)
			{
				// The scalars of the parametric line intersection equation
				float ray_t = 1.f;
				float line_s = 0.0f;

				if (occluder_intersect(light_centre, *ray, ray_t, line_s))
				{
					light_geom.push_back(sf::Vector2f(ray->x * ray_t, ray->y * ray_t));
				}
				
				// If the coefficients are these values, then we are hitting a corner of an occluder
				// Fire two more rays, + and - 0.00001f radians different from original ray
				if (ray_t == 1.f && (line_s == 0.f || line_s == 1.f))
				{
					ray_t = INFINITY;
					line_s = 0.f;
						
					float dx = ray->x * (std::cos(0.00001f)) - ray->y * (std::sin(0.00001f));
					float dy = ray->x * (std::sin(0.00001f)) + ray->y * (std::cos(0.00001f));

					sf::Vector2f new_ray(dx, dy);

					level_bound_intersect(light_centre, new_ray, ray_t, line_s);

					new_ray *= ray_t;
					ray_t = 1.f;
					line_s = 0.f;

					occluder_intersect(light_centre, new_ray, ray_t, line_s);

					light_geom.push_back(new_ray * ray_t);
					
					ray_t = INFINITY;
					line_s = 0.f;

					dx = ray->x * (std::cos(-0.00001f)) - ray->y * (std::sin(-0.00001f));
					dy = ray->x * (std::sin(-0.00001f)) + ray->y * (std::cos(-0.00001f));

					new_ray = sf::Vector2f(dx, dy);

					level_bound_intersect(light_centre, new_ray, ray_t, line_s);

					new_ray *= ray_t;
					ray_t = 1.f;
					line_s = 0.f;

					occluder_intersect(light_centre, new_ray, ray_t, line_s);

					light_geom.push_back(new_ray * ray_t);
				}
			}
		}

		// Cast final rays at the corners of the map
		{
			sf::Vector2f map_tl(0.f, 0.f);
			sf::Vector2f map_tr(level.get_map_width() * 32.f, 0.f);
			sf::Vector2f map_bl(0.f, level.get_map_height() * 32.f);
			sf::Vector2f map_br(level.get_map_width() * 32.f, level.get_map_height() * 32.f);

			std::vector<sf::Vector2f> rays;
			rays.push_back(map_tl - light_centre);
			rays.push_back(map_tr - light_centre);
			rays.push_back(map_bl - light_centre);
			rays.push_back(map_br - light_centre);

			for (auto& ray : rays)
			{
				float ray_t = 1.0f;
				float line_s = 0.f;

				occluder_intersect(light_centre, ray, ray_t, line_s);
				light_geom.push_back(ray * ray_t);
			}
		}

		// Sort the light rays by their angle
		std::sort(light_geom.begin(), light_geom.end(), compare_ray_angle);

		// Construct the geometry
		// sf::TriangleFan doesn't seem to work for some reason, so just make all the triangles instead
		for (int i = 0; i < light_geom.size() - 1; i++)
		{
			varr.append(light_centre);
			varr.append(sf::Vertex(light_centre + light_geom[i]));
			varr.append(sf::Vertex(light_centre + light_geom[i+1]));
		}

		varr.append(light_centre);
		varr.append(sf::Vertex(light_centre + light_geom[light_geom.size() - 1]));
		varr.append(sf::Vertex(light_centre + light_geom[0]));

		_light_shader.setUniform("centre", light_centre);
		_light_shader.setUniform("radius", light->radius * 32.f);
		_light_shader.setUniform("tex", _light_map.getTexture());

		_occlusion_map.draw(varr, &_light_shader);
		_occlusion_map.display();

		_light_map.draw(sf::Sprite(_occlusion_map.getTexture()));
	}

	_light_map.display();
}

bool LightSystem::occluder_intersect(const sf::Vector2f& origin, const sf::Vector2f& direction, float& t, float& s)
{
	const Level& level = Environment::get().get_level_manager()->get_current();
	bool intersects = false;

	// Check for intersection with occluder cells
	for (auto& occ2 : level._occluders)
	{
		sf::Vector2f oc(occ2->_x * 32.f + 16.f, occ2->_y * 32.f + 16.f);

		// Corners of the square that the occluder occupies
		sf::Vector2f tl = oc + sf::Vector2f(-16.f, -16.f);
		sf::Vector2f tr = oc + sf::Vector2f(16.f, -16.f);
		sf::Vector2f bl = oc + sf::Vector2f(-16.f, 16.f);
		sf::Vector2f br = oc + sf::Vector2f(16.f, 16.f);

		// Lines of the occluder square in parametric form (u + tv)
		std::pair<sf::Vector2f, sf::Vector2f> lines[4];
		lines[0] = std::pair<sf::Vector2f, sf::Vector2f>(tl, tr - tl);
		lines[1] = std::pair<sf::Vector2f, sf::Vector2f>(tr, br - tr);
		lines[2] = std::pair<sf::Vector2f, sf::Vector2f>(tl, bl - tl);
		lines[3] = std::pair<sf::Vector2f, sf::Vector2f>(bl, br - bl);

		for (int i = 0; i < 4; i++)
		{
			float determinant = lines[i].second.x * direction.y - lines[i].second.y * direction.x;

			if (determinant == 0.0f)
				continue;

			float _s = (direction.x * (lines[i].first.y - origin.y) + direction.y * (origin.x - lines[i].first.x)) / determinant;

			if (_s < 0.0f || _s > 1.0f)
				continue;

			float _t = (lines[i].first.x + (lines[i].second.x * _s) - origin.x) / direction.x;

			if (_t <= 0.0f)
				continue;

			if (_t <= t)
			{
				t = _t;
				s = _s;
				intersects = true;
			}
		}
	}

	return intersects;
}

bool LightSystem::level_bound_intersect(const sf::Vector2f& origin, const sf::Vector2f& direction, float& t, float& s)
{
	const Level& level = Environment::get().get_level_manager()->get_current();
	bool intersects = false;

	// Check for intersection with level bounds
	sf::Vector2f tl = sf::Vector2f(0.f, 0.f);
	sf::Vector2f tr = sf::Vector2f(level.get_map_width() * 32.f, 0.f);
	sf::Vector2f bl = sf::Vector2f(0.f, level.get_map_height() * 32.f);
	sf::Vector2f br = sf::Vector2f(level.get_map_width() * 32.f, level.get_map_width() * 32.f);

	// Lines of the level bounds in parametric form (u + tv)
	std::pair<sf::Vector2f, sf::Vector2f> lines[4];
	lines[0] = std::pair<sf::Vector2f, sf::Vector2f>(tl, tr - tl);
	lines[1] = std::pair<sf::Vector2f, sf::Vector2f>(tr, br - tr);
	lines[2] = std::pair<sf::Vector2f, sf::Vector2f>(tl, bl - tl);
	lines[3] = std::pair<sf::Vector2f, sf::Vector2f>(bl, br - bl);

	for (int i = 0; i < 4; i++)
	{
		float determinant = lines[i].second.x * direction.y - lines[i].second.y * direction.x;

		if (determinant == 0.0f)
			continue;

		float _s = (direction.x * (lines[i].first.y - origin.y) + direction.y * (origin.x - lines[i].first.x)) / determinant;

		if (_s < 0.0f || _s > 1.0f)
			continue;

		float _t = (lines[i].first.x + (lines[i].second.x * _s) - origin.x) / direction.x;

		if (_t <= 0.0f)
			continue;

		if (_t <= t)
		{
			t = _t;
			s = _s;
			intersects = true;
		}
	}

	return intersects;
}

bool LightSystem::compare_ray_angle(const sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
	float lhs_theta = std::acos(dot(world_right, normalise(sf::Vector2f(lhs.x, -lhs.y))));

	if (lhs.y > 0)
		lhs_theta = (2.f * M_PI) - lhs_theta;

	float rhs_theta = std::acos(dot(world_right, normalise(sf::Vector2f(rhs.x, -rhs.y))));

	if (rhs.y > 0)
		rhs_theta = (2.f * M_PI) - rhs_theta;

	return lhs_theta < rhs_theta;
}

const sf::RenderTexture& LightSystem::get_lightmap(void) const
{
	return _light_map;
}

void LightSystem::receive(const EntityCreated& event)
{
	if(event.entity->has_component<LightSource>())
		_entities.push_back(event.entity);
}
