#include "game_time.h"

using namespace std::chrono;

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
	_elapsed = move(duration<double>(0));
}

bool Timer::finished(void) const
{
	return _finished;
}
