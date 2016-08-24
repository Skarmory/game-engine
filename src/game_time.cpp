#include "game_time.h"

GameTime::GameTime(void) : _current(high_resolution_clock::now()), _previous(high_resolution_clock::now()) {}

void GameTime::tick(void)
{
	_current = high_resolution_clock::now();

	_delta = _current - _previous;

	_previous = _current;
}

double GameTime::delta(void) const
{
	return _delta.count();
}

Timer::Timer(double duration) : _count_to(duration), _finished(false) {}	

void Timer::tick(const GameTime& time)
{
	if(!_finished)
	{
		_elapsed += duration<double>(time.delta());
		
		if(_elapsed >= _count_to)
		{
			_finished = true;
		}
	}
}

double Timer::time_elapsed(void) const
{
	return _elapsed.count();
}

void Timer::reset(void)
{
	_finished = false;
	_elapsed = duration<double>(0);
}

bool Timer::finished(void) const
{
	return _finished;
}
