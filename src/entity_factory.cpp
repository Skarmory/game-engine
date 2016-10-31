#include "entity_factory.h"

EntityFactory::EntityFactory(void)
{
	_create_methods["player"]  = &EntityFactory::create_player;
	_create_methods["fire"]    = &EntityFactory::create_fire;
	_create_methods["damage"]  = &EntityFactory::create_damage;
	_create_methods["aoe_dmg"] = &EntityFactory::create_aoe_dmg;
}
	
unique_ptr<Entity> EntityFactory::create(int id, string type)
{
	if(_create_methods[type])
		return (this->*_create_methods[type])(id);
	return nullptr;
}


unique_ptr<Entity> EntityFactory::create_player(int id)
{
	unique_ptr<Entity> e(new Entity(id));
	e->add_component(make_shared<Location>());
	e->add_component(make_shared<Graphic>('@', TCODColor::white, TCODColor::black, DrawLayer::CREATURE));
	e->add_component(make_shared<Collision>());
	e->add_component(make_shared<Health>(1));
	e->add_component(make_shared<LightSource>(10));
	e->add_component(make_shared<Sight>(20));
	return e;
}

unique_ptr<Entity> EntityFactory::create_fire(int id)
{
	unique_ptr<Entity> e(new Entity(id));
	e->add_component(make_shared<Location>());
	e->add_component(make_shared<Graphic>('F', TCODColor::orange, TCODColor::darkOrange, DrawLayer::EFFECT));
	e->add_component(make_shared<Collision>());
	e->add_component(make_shared<Damage>(1));
	e->add_component(make_shared<LightSource>(20));
	return e;
}

unique_ptr<Entity> EntityFactory::create_damage(int id)
{
	unique_ptr<Entity> e(new Entity(id));
	e->add_component(make_shared<Location>());
	e->add_component(make_shared<Graphic>('.', TCODColor::black, TCODColor::darkerYellow, DrawLayer::AREADMG));
	e->add_component(make_shared<Collision>());
	e->add_component(make_shared<PeriodicDamage>(1, 2));
	e->add_component(make_shared<TimedHealth>(2));
	return e;
}

unique_ptr<Entity> EntityFactory::create_aoe_dmg(int id)
{
	unique_ptr<Entity> e(new Entity(id));
	
	e->add_component(make_shared<Location>());
	e->add_component(make_shared<Graphic>('.', TCODColor::black, TCODColor::lightestCyan, DrawLayer::AREADMG));
	e->add_component(make_shared<Collision>());
	e->add_component(make_shared<PeriodicDamage>(2, 3));

	return e;
}
