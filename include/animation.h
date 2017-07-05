#ifndef animation_h
#define animation_h

#include <unordered_map>
#include <string>

#include "component.h"
#include "system.h"
#include "event.h"
#include "events.h"

struct Animation
{
	std::string name;
	int frame_count;
	int start_frame;
	int end_frame;
	double duration;
	double interval;
};

struct Animator : public Component<Animator>
{
	std::unordered_map<std::string, Animation*> animations;
	Animation* current;
	int current_frame;
	double running_time;
	double frame_time;

	bool play(const std::string& anim_id);
};

class AnimationSystem : public System, public sov::Observer<EntityCreated>
{
public:
	void init(void) override;
	void update(void) override;
	void receive(const EntityCreated& e) override;
};

class AnimationLoader
{
private:
	const std::string _path = "resources/anim/";

public:
	bool load(const std::string& anim_id, std::vector<Animation*>* anim);
};

class AnimationCache
{
private:	
	std::unordered_map<std::string, std::vector<Animation*>> _cache;
	AnimationLoader _loader;

	bool _has(const std::string& anim_id);
	bool _load(const std::string& anim_id);

public:
	~AnimationCache(void);
	std::vector<Animation*>* get(const std::string& anim_id);
};

#endif