#ifndef environment_h
#define environment_h

#include "entity_manager.h"
#include "event.h"
#include "input.h"
#include "level_manager.h"
#include "system.h"
#include "sprite.h"
#include "animation.h"
#include "game_time.h"

// This class is an access point for all the managers in the game

class Environment
{
	static Environment* env;

	EntityManager* _entity_manager;
	InputManager* _input_manager;
	SystemManager* _system_manager;
	sov::EventManager* _event_manager;
	LevelManager* _level_manager;
	SpriteCache* _sprite_cache;
	AnimationCache* _anim_cache;
	GameTime* _game_time;

public:
	explicit Environment(void);
	~Environment(void);

	void set_entity_manager(EntityManager* entity_manager);
	void set_system_manager(SystemManager* system_manager);
	void set_event_manager(sov::EventManager* event_manager);
	void set_level_manager(LevelManager* level_manager);
	void set_input_manager(InputManager* input_manager);
	void set_sprite_cache(SpriteCache* sprite_cache);
	void set_animation_cache(AnimationCache* sprite_cache);
	void set_game_time(GameTime* game_time);

	EntityManager* get_entity_manager(void) const;
	SystemManager* get_system_manager(void) const;
	sov::EventManager* get_event_manager(void) const;
	LevelManager* get_level_manager(void) const;
	InputManager* get_input_manager(void) const;
	SpriteCache* get_sprite_cache(void) const;
	AnimationCache* get_animation_cache(void) const;
	GameTime* get_game_time(void) const;

	static const Environment& get(void);
};

#endif