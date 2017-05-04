#include "move_system.h"

#include "environment.h"
#include "graphics.h"

#include <iostream>

void MoveSystem::init(void)
{
	Environment::get().get_event_manager()->subscribe<MoveEvent>(*this);
}

void MoveSystem::update(void)
{
	for (auto it = _entities.begin(); it != _entities.end();)
	{
		Move* move = (*it)->get_component<Move>();
		sov::Graphics* gfx = (*it)->get_component<sov::Graphics>();

		float dest_x = (float)move->dest_x * 32.0f;
		float dest_y = (float)move->dest_y * 32.0f;
		double delta = Environment::get().get_game_time()->delta();
		move->t += MOVE_SPEED * delta;

		float x = (1 - move->t) * move->from_x + move->t * dest_x;
		float y = (1 - move->t) * move->from_y + move->t * dest_y;

		/*if(dest_x > move->current_x)
			move->current_x += MOVE_SPEED * delta;
		else if (dest_x < move->current_x)
			move->current_x -= MOVE_SPEED * delta;

		if (dest_y > move->current_y)
			move->current_y += MOVE_SPEED * delta;
		else if (dest_y < move->current_y)
			move->current_y -= MOVE_SPEED * delta;

		if (std::abs(move->current_x - dest_x) <= 2.f)
			move->current_x = dest_x;

		if (std::abs(move->current_y - dest_y) <= 2.f)
			move->current_y = dest_y;*/

		gfx->sprite.setPosition(x, y);

		if (move->t >= 1.f)
		{
			gfx->sprite.setPosition(dest_x, dest_y);
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