#ifndef loaders_h
#define loaders_h

#include <string>
#include <rapidxml-1.13\rapidxml.hpp>
#include <sstream>

#include "entity.h"
#include "components.h"

class ComponentLoader
{
public:
	virtual ~ComponentLoader(void) = default;
	virtual void load(rapidxml::xml_node<char>* node, Entity& entity) = 0;
};

class LocationLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override
	{
		prototype.add_component(make_shared<Location>());
	}

};

class CollisionLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override
	{
		prototype.add_component(make_shared<Collision>());
	}
};

class DamageLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override
	{
		stringstream ss;
		int damage;
		ss << node->value();
		ss >> damage;
		prototype.add_component(make_shared<Damage>(damage));
	}
};

class PeriodicDamageLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override
	{
		stringstream ss;
		int damage, period;
		
		auto n = node->first_node();

		do
		{
			if (n->name() == "damage")
			{
				ss << n->value();
				ss >> damage;
			}
			else if (n->name() == "period")
			{
				ss << n->value();
				ss >> period;
			}
		}
		while ((n = n->next_sibling()) != 0);

		prototype.add_component(make_shared<PeriodicDamage>(damage, period));
	}
};

class GraphicLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& entity) override
	{
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
		} 
		while ((n = n->next_sibling()) != 0);

		entity.add_component(make_shared<Graphic>(c, fg, bg, l));
	}
};

class HealthLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override
	{
		stringstream ss;
		int health;
		ss << node->value();
		ss >> health;
		prototype.add_component(make_shared<Health>(health));
	}
};

class SightLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override
	{
		stringstream ss;
		int radius;
		ss << node->value();
		ss >> radius;
		prototype.add_component(make_shared<Sight>(radius));
	}
};

class LightSourceLoader : public ComponentLoader
{
public:
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override
	{
		stringstream ss;
		int radius;
		ss << node->value();
		ss >> radius;
		prototype.add_component(make_shared<LightSource>(radius));
	}
};

#endif
