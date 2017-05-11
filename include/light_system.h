#ifndef light_system_h
#define light_system_h

#include "system.h"
#include "events.h"
#include "ui.h"

class LightSystem : public System, public sov::Observer<EntityCreated>
{
public:
	explicit LightSystem(void) {}

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& event) override;

	const sf::RenderTexture& get_lightmap(void) const;

private:
	const std::string _shader_path = "resources/shaders/";

	//Viewport* _viewport;
	sf::RenderTexture _light_map;
	sf::RenderTexture _occlusion_map;
	sf::Shader _light_shader;

	bool occluder_intersect(const sf::Vector2f& origin, const sf::Vector2f& direction, float& t, sf::Vector2f& closest = sf::Vector2f(0.f, 0.f));
	bool level_bound_intersect(const sf::Vector2f& origin, const sf::Vector2f& direction, float& t);

	static bool compare_ray_angle(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
};

#endif
