#include "command.h"
using namespace std;
using namespace Command;

MoveCommand::MoveCommand(weak_ptr<Entity> e, weak_ptr<Level> l, int x, int y) :
   	_entity(e), _level(l), _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	if(shared_ptr<Entity> e = _entity.lock())
	{
		if(shared_ptr<Level> lev = _level.lock())
		{
			int dx, dy;
			shared_ptr<LocationComponent> lc = e->get_component<LocationComponent>();
				
			dx = lc->x + _x;
			dy = lc->y + _y;

			if(lev->is_in_bounds(dx, dy) && lev->is_walkable(dx, dy))
			{
				lc->x = dx;
				lc->y = dy;	
			}
		}
	}
}

AttackCommand::AttackCommand(weak_ptr<Entity> attacker, int x, int y) 
	: _attacker(attacker), _x(x), _y(y) {}

void AttackCommand::execute(void)
{
	if(shared_ptr<Entity> atker = _attacker.lock())
	{
		if(atker->has_component<LocationComponent>())
		{
			shared_ptr<LocationComponent> loc = atker->get_component<LocationComponent>();

			// TODO: Remove hardcoded damage
			shared_ptr<Entity> en = EntityManager::get_instance().create_entity();
			en->add_component(make_shared<LocationComponent>(loc->x + _x, loc->y + _y));
			en->add_component(make_shared<DamageComponent>(1)); 			
			en->add_component(make_shared<GraphicComponent>(' ', TCODColor::black, TCODColor::yellow, DrawLayer::AREADMG));
			en->add_component(make_shared<TimedLifeComponent>(1));
			en->add_component(make_shared<CollisionComponent>());
		}
	}
}	

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}
