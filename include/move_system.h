#ifndef move_system_h
#define move_system_h

#include "system.h"
#include "events.h"
#include "component.h"

struct Move : public Component<Move>
{
	explicit Move(int dest_x, int dest_y, float from_x, float from_y, float t) : dest_x(dest_x), dest_y(dest_y), from_x(from_x), from_y(from_y), t(t) {}

	int dest_x, dest_y;
	float from_x, from_y;
	float t;
};

class MoveSystem : public System, public sov::Observer<MoveEvent>
{
public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const MoveEvent& e) override;

	const float MOVE_SPEED = 8.f;
};

#endif
