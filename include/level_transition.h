#ifndef level_transition_h
#define level_transition_h

#include "component.h"

struct LevelTransition : public Component<LevelTransition>
{
	explicit LevelTransition(void) : next_level_name(""), next_level_x(-1), next_level_y(-1), next_level_z(-1) {}
	explicit LevelTransition(const string& next_level_name, int next_level_x, int next_level_y, int next_level_z) 
		: next_level_name(next_level_name), next_level_x(next_level_x), next_level_y(next_level_y), next_level_z(next_level_z) {}

	const string& next_level_name;
	int next_level_x, next_level_y, next_level_z;
};

#endif // !level_transition_h
