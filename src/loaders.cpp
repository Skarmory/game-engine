#include "loaders.h"

void LocationLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	prototype.add_component(make_shared<Location>());
}

void CollisionLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	prototype.add_component(make_shared<Collision>());
}

void DamageLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	stringstream ss;
	int damage = 0;
	ss << node->value();
	ss >> damage;
	prototype.add_component(make_shared<Damage>(damage));
}

void PeriodicDamageLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	stringstream ss;
	int damage = 0;
	int period = 0;

	auto n = node->first_node();

	do
	{
		ss.clear();
		ss << n->value();

		if (n->name() == string("damage"))
			ss >> damage;
		else if (n->name() == string("period"))
			ss >> period;

	} while ((n = n->next_sibling()) != 0);

	prototype.add_component(make_shared<PeriodicDamage>(damage, period));
}

void GraphicLoader::load(rapidxml::xml_node<char>* node, Entity& entity)
{
	using namespace sov;

	stringstream ss;
	auto n = node->first_node();

	char c;
	Color fg, bg;
	DrawLayer l;

	do
	{
		if (strcmp(n->name(), "character") == 0)
		{
			c = n->value()[0] != '\0' ? n->value()[0] : ' ';
		}
		else if (strcmp(n->name(), "foregroundColour") == 0)
		{
			string colour_name = n->value();
			fg = colours_map.at(colour_name);
		}
		else if (strcmp(n->name(), "backgroundColour") == 0)
		{
			string colour_name = n->value();
			bg = colours_map.at(colour_name);
		}
		else if (strcmp(n->name(), "layer") == 0)
		{
			ss << n->value();
			int i;
			ss >> i;
			l = static_cast<DrawLayer>(i);
		}
	} while ((n = n->next_sibling()) != 0);

	entity.add_component(make_shared<Graphic>(c, fg, bg, l));
}

void HealthLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	stringstream ss;
	int health = 0;
	ss << node->value();
	ss >> health;
	prototype.add_component(make_shared<Health>(health));
}

void SightLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	stringstream ss;
	int radius = 0;
	ss << node->value();
	ss >> radius;
	prototype.add_component(make_shared<Sight>(radius));
}

void LightSourceLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	stringstream ss;
	int radius = 0;
	ss << node->value();
	ss >> radius;
	prototype.add_component(make_shared<LightSource>(radius));
}

void LevelTransitionLoader::load(rapidxml::xml_node<char>* node, Entity& prototype)
{
	prototype.add_component(make_shared<LevelTransition>());
}