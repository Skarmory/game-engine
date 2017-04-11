#ifndef move_system_h
#define move_system_h

#include "system.h"
#include "events.h"
#include "component.h"

struct Move : public Component<Move>
{
	explicit Move(int dest_x, int dest_y, float current_x, float current_y) : dest_x(dest_x), dest_y(dest_y), current_x(current_x), current_y(current_y) {}

	int dest_x, dest_y;
	float current_x, current_y;
};

class MoveSystem : public System, public sov::Observer<MoveEvent>
{
public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const MoveEvent& e) override;

	const float MOVE_SPEED = 4.0f;
};

#endif
