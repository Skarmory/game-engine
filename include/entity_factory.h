#ifndef entity_factory_h
#define entity_factory_h

#include <string>
#include <map>

#include "libtcod.h"
#include "components.h"

using namespace std;

class EntityFactory 
{
public:
	EntityFactory(void)
	{
		_create_methods["player"] = &EntityFactory::create_player;
		_create_methods["fire"]   = &EntityFactory::create_fire;
		_create_methods["damage"] = &EntityFactory::create_damage;
	}
	~EntityFactory(void) = default;
	
	shared_ptr<Entity> create(int id, string type)
	{
		if(_create_methods[type])
			return (this->*_create_methods[type])(id);
		return nullptr;
	}

private:
	map<string, shared_ptr<Entity> (EntityFactory::*)(int)> _create_methods;

	shared_ptr<Entity> create_player(int id)
	{
		shared_ptr<Entity> e = make_shared<Entity>(id);
		e->add_component(make_shared<LocationComponent>());
		e->add_component(make_shared<GraphicComponent>('@', TCODColor::white, TCODColor::black, DrawLayer::CREATURE));
		e->add_component(make_shared<CollisionComponent>());
		e->add_component(make_shared<HealthComponent>(1));
		return e;
	}

	shared_ptr<Entity> create_fire(int id)
	{
		shared_ptr<Entity> e = make_shared<Entity>(id);
		e->add_component(make_shared<LocationComponent>());
		e->add_component(make_shared<GraphicComponent>('F', TCODColor::orange, TCODColor::darkOrange, DrawLayer::EFFECT));
		e->add_component(make_shared<CollisionComponent>());
		e->add_component(make_shared<DamageComponent>(1));
		return e;
	}

	shared_ptr<Entity> create_damage(int id)
	{
		shared_ptr<Entity> e = make_shared<Entity>(id);
		e->add_component(make_shared<LocationComponent>());
		e->add_component(make_shared<GraphicComponent>('.', TCODColor::black, TCODColor::yellow, DrawLayer::AREADMG));
		e->add_component(make_shared<CollisionComponent>());
		e->add_component(make_shared<DamageComponent>(1));
		//e->add_component(make_shared<TimedLifeComponent>(3));
		return e;
	}
};

#endif
