#ifndef sight_h
#define sight_h

#include "component.h"

struct Sight : public Component<Sight>
{
	explicit Sight(int radius) : radius(radius) {}

	int radius;
};

#endif // !sight_h
