#include "environment.h"

Environment* Environment::env = nullptr;

Environment::Environment(void) 
	: _entity_manager(nullptr), _event_manager(nullptr), _level_manager(nullptr), _input_manager(nullptr),
	_system_manager(nullptr), _sprite_cache(nullptr)
{
	Environment::env = this;
}

Environment::~Environment(void)
{
	/*if(_entity_manager != nullptr)
		delete _entity_manager;

	if (_system_manager != nullptr)
		delete _system_manager;

	if (_level_manager != nullptr)
		delete _level_manager;

	if (_input_manager != nullptr)
		delete _input_manager;

	if (_event_manager != nullptr)
		delete _event_manager;*/

	env = nullptr;
}

void Environment::set_entity_manager(EntityManager* entity_manager)
{
	_entity_manager = entity_manager;
}

void Environment::set_system_manager(SystemManager* system_manager)
{
	_system_manager = system_manager;
}

void Environment::set_event_manager(sov::EventManager* event_manager)
{
	_event_manager = event_manager;
}

void Environment::set_input_manager(InputManager* input_manager)
{
	_input_manager = input_manager;
}

void Environment::set_level_manager(LevelManager* level_manager)
{
	_level_manager = level_manager;
}

void Environment::set_sprite_cache(SpriteCache* sprite_cache)
{
	_sprite_cache = sprite_cache;
}

EntityManager* Environment::get_entity_manager(void) const
{
	return _entity_manager;
}

SystemManager* Environment::get_system_manager(void) const
{
	return _system_manager;
}

sov::EventManager* Environment::get_event_manager(void) const
{
	return _event_manager;
}

LevelManager* Environment::get_level_manager(void) const
{
	return _level_manager;
}

InputManager* Environment::get_input_manager(void) const
{
	return _input_manager;
}

SpriteCache* Environment::get_sprite_cache(void) const
{
	return _sprite_cache;
}

const Environment& Environment::get(void)
{
	return *env;
}