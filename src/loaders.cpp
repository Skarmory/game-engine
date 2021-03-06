#include "loaders.h"

#include <string>
#include <memory>

#include "environment.h"
#include "location.h"
#include "collision.h"
#include "damage.h"
#include "graphics.h"
#include "health.h"
#include "sight.h"
#include "light.h"
#include "level_transition.h"
#include "animation.h"

void LocationLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(new Location());
}

void CollisionLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(new Collision());
}

void DamageLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(new Damage(std::stoi(value)));
}

void GraphicLoader::load(Entity& entity, const std::string& value)
{
	sf::Sprite sprite;
	sf::Transform trans;
	sov::DrawLayer layer;

	std::string vals[2];

	size_t ppos = 0;
	for (int i = 0; i < 2; i++)
	{
		size_t pos = value.find(':', ppos);
		if (pos == std::string::npos)
			pos = value.length();

		vals[i] = value.substr(ppos, pos-ppos);
		ppos = pos + 1;
	}

	sprite = sf::Sprite(*(Environment::get().get_sprite_cache()->get(vals[0])));
	layer = static_cast<sov::DrawLayer>(std::stoi(vals[1]));

	entity.add_component(new sov::Graphics(sprite, trans, layer));
}

void HealthLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(new Health(std::stoi(value)));
}

void SightLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(new Sight(std::stoi(value)));
}

void LightSourceLoader::load(Entity& prototype, const std::string& value)
{
	std::string vals[2];

	size_t ppos = 0;
	for (int i = 0; i < 2; i++)
	{
		size_t pos = value.find(':', ppos);
		if (pos == std::string::npos)
			pos = value.length();

		vals[i] = value.substr(ppos, pos - ppos);
		ppos = pos + 1;
	}

	prototype.add_component(new LightSource(std::stoi(vals[0]), std::stoi(vals[1])));
}

void LevelTransitionLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(new LevelTransition());
}

void AnimatorLoader::load(Entity& prototype, const std::string& value)
{
	Animator* animator = new Animator();

	if (value != "null")
	{
		std::vector<Animation*>* anims = Environment::get().get_animation_cache()->get(value);

		for (auto anim : *anims)
			animator->animations[anim->name] = anim;

		animator->current = animator->animations["idle"];
	}

	animator->current_frame = 0;
	animator->frame_time = 0.0;
	animator->running_time = 0.0;

	prototype.add_component(animator);
}