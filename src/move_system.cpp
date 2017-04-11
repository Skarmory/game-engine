#include "move_system.h"

#include "environment.h"
#include "graphics.h"

void MoveSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<MoveEvent>(*this);
}

void MoveSystem::update(void)
{
	for (entity_iterator it = _entities.begin(); it != _entities.end();)
	{
		Move* move = (*it)->get_component<Move>();
		sov::Graphics* gfx = (*it)->get_component<sov::Graphics>();

		float dest_x = (float)move->dest_x * 32.0f;
		float dest_y = (float)move->dest_y * 32.0f;

		if(dest_x > move->current_x)
			move->current_x += MOVE_SPEED;
		else if (dest_x < move->current_x)
			move->current_x -= MOVE_SPEED;

		if (dest_y > move->current_y)
			move->current_y += MOVE_SPEED;
		else if (dest_y < move->current_y)
			move->current_y -= MOVE_SPEED;

		gfx->sprite.setPosition(move->current_x, move->current_y);

		if (move->current_y == dest_y && move->current_x == dest_x)
		{
			(*it)->remove_component<Move>();
			it = _entities.erase(it);
			continue;
		}

		++it;
	}
}

void MoveSystem::receive(const MoveEvent& event)
{
	_entities.push_back(event.entity);
}