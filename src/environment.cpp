#include "environment.h"

Environment* Environment::env = nullptr;

Environment::Environment(void) 
	: _entity_manager(nullptr), _input_manager(nullptr), _system_manager(nullptr), _event_manager(nullptr), _level_manager(nullptr),
	 _sprite_cache(nullptr), _anim_cache(nullptr), _game_time(nullptr)
{
	Environment::env = this;
}

Environment::~Environment(void)
{
	delete _entity_manager;
	delete _input_manager;
	delete _system_manager;
	delete _event_manager;
	delete _level_manager;
	delete _sprite_cache;
	delete _anim_cache;
	delete _game_time;

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

void Environment::set_animation_cache(AnimationCache* anim_cache)
{
	_anim_cache = anim_cache;
}
void Environment::set_game_time(GameTime* game_time)
{
	_game_time = game_time;
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

AnimationCache* Environment::get_animation_cache(void) const
{
	return _anim_cache;
}

GameTime* Environment::get_game_time(void) const
{
	return _game_time;
}

const Environment& Environment::get(void)
{
	return *env;
}