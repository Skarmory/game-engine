#include "animation.h"

#include <fstream>
#include <sstream>

#include <iostream>

#include "environment.h"

bool Animator::play(const std::string& anim_id)
{
	if (animations.find(anim_id) != animations.end())
	{
		current = animations.at(anim_id);
		running_time = 0.0;
		frame_time = 0.0;
		current_frame = current->start_frame;

		return true;
	}

	return false;
}

void AnimationSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<EntityCreated>(*this);
}

void AnimationSystem::update(void)
{
	for (auto entity : _entities)
	{
		Animator* anim = entity->get_component<Animator>();

		if (anim->current == nullptr || anim->current->frame_count <= 1)
			continue;

		anim->running_time += Environment::get().get_game_time()->delta();
		anim->frame_time += Environment::get().get_game_time()->delta();

		// Go to next frame
		if (anim->frame_time >= anim->current->interval)
		{
			anim->current_frame++;
			anim->frame_time = 0.0f;
		}

		// Animation has ended, set back to start
		if (anim->running_time >= anim->current->duration)
		{
			anim->current_frame = anim->current->start_frame;
			anim->running_time = 0.0f;
			anim->frame_time = 0.0f;
		}
	}
}

void AnimationSystem::receive(const EntityCreated& e)
{
	if (e.entity->has_component<Animator>())
		_entities.push_back(e.entity);
}

bool AnimationCache::_has(const std::string& anim_id)
{
	return _cache.find(anim_id) != _cache.end();
}

bool AnimationCache::_load(const std::string& anim_id)
{
	bool ret = false;
	std::vector<Animation*> anim;
	
	ret = _loader.load(anim_id, &anim);

	if(ret)
		_cache[anim_id] = anim;

	return ret;
}

AnimationCache::~AnimationCache(void)
{
	for (auto& anim : _cache)
		for (auto& elem : anim.second)
			delete elem;
}

std::vector<Animation*>* AnimationCache::get(const std::string& anim_id)
{
	if (!_has(anim_id))
		_load(anim_id);

	return &_cache[anim_id];
}

bool AnimationLoader::load(const std::string& anim_id, std::vector<Animation*>* anim)
{
	std::stringstream ss;
	std::ifstream fs;
	std::string line, option, value;
	bool found = false;

	ss << _path << anim_id << ".txt";

	fs.open(ss.str());

	while (std::getline(fs, line))
	{
		if (line[0] == '#' || line.find_first_not_of(' ') == std::string::npos)
			continue;

		found = true;
		Animation* a = new Animation();

		while (line[0] != '#' && line.find_first_not_of(' ') != std::string::npos)
		{
			std::size_t position = line.find('=');
			option = line.substr(0, position);
			value = line.substr(position + 1, line.length());

			if (option == "name")
			{
				a->name = value;
			}
			else if (option == "count")
			{
				a->frame_count = std::stoi(value);
			}
			else if (option == "start")
			{
				a->start_frame = std::stoi(value);
			}
			else if (option == "end")
			{
				a->end_frame = std::stoi(value);
			}
			else if (option == "duration")
			{
				a->duration = std::stoi(value) / 1000.f;
			}

			a->interval = (a->duration / a->frame_count);

			std::getline(fs, line);
		}

		anim->push_back(a);
	}

	fs.close();

	return found;
}