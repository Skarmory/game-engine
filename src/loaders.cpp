#include "loaders.h"

#include <string>
#include <memory>

#include "environment.h"
#include "location.h"
#include "collision.h"
#include "damage.h"
#include "graphic.h"
#include "health.h"
#include "sight.h"
#include "light.h"
#include "level_transition.h"

void LocationLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(make_shared<Location>());
}

void CollisionLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(make_shared<Collision>());
}

void DamageLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(make_shared<Damage>(std::stoi(value)));
}

void PeriodicDamageLoader::load(Entity& prototype, const std::string& value)
{
	int damage = 0;
	int period = 0;

	prototype.add_component(make_shared<PeriodicDamage>(damage, period));
}

void GraphicLoader::load(Entity& entity, const std::string& value)
{
	sf::Sprite sprite;
	sf::Transform trans;
	sov::DrawLayer layer;

	std::string vals[2];

	size_t ppos = 0, pos = 0;
	for (int i = 0; i < 2; i++)
	{
		pos = value.find(':', ppos);
		if (pos == std::string::npos)
			pos = value.length();

		vals[i] = value.substr(ppos, pos-ppos);
		ppos = pos + 1;
	}

	sprite = sf::Sprite(*(Environment::get().get_sprite_cache()->get(vals[0])));
	layer = static_cast<sov::DrawLayer>(std::stoi(vals[1]));

	entity.add_component(make_shared<sov::Graphic>(sprite, trans, layer));
}

void HealthLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(make_shared<Health>(std::stoi(value)));
}

void SightLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(make_shared<Sight>(std::stoi(value)));
}

void LightSourceLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(make_shared<LightSource>(std::stoi(value)));
}

void LevelTransitionLoader::load(Entity& prototype, const std::string& value)
{
	prototype.add_component(make_shared<LevelTransition>());
}