#ifndef loaders_h
#define loaders_h

#include <cstring>
#include <rapidxml-1.13/rapidxml.hpp>

#include "entity.h"

class ComponentLoader
{
public:
	virtual ~ComponentLoader(void) = default;
	virtual void load(rapidxml::xml_node<char>* node, Entity& entity) = 0;
};

class LocationLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

class CollisionLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

class DamageLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

class PeriodicDamageLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

class GraphicLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& entity) override;
};

class HealthLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

class SightLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

class LightSourceLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

class LevelTransitionLoader : public ComponentLoader
{
	void load(rapidxml::xml_node<char>* node, Entity& prototype) override;
};

#endif
