#ifndef loaders_h
#define loaders_h

#include "entity.h"

class ComponentLoader
{
public:
	virtual ~ComponentLoader(void) = default;
	virtual void load(Entity& prototype, const std::string& value) = 0;
};

class LocationLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class CollisionLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class DamageLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class PeriodicDamageLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class GraphicLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class HealthLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class SightLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class LightSourceLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

class LevelTransitionLoader : public ComponentLoader
{
	void load(Entity& prototype, const std::string& value) override;
};

#endif
