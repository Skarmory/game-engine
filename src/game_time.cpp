#include "game_time.h"

using namespace std::chrono;

void GameTime::tick(void)
{
	_previous = _current;

	_current = high_resolution_clock::now();

	_delta = _current - _previous;
}

double GameTime::delta(void) const
{
	return _delta.count();
}

void Timer::tick(const GameTime& time)
{
	if(!_finished)
	{
		_elapsed += time.delta();
		
		if(_elapsed >= _count_to)
		{
			_finished = true;
		}
	}
}

double Timer::time_elapsed(void) const
{
	return _elapsed;
}

void Timer::reset(void)
{
	_finished = false;
	_elapsed = 0;
}

bool Timer::finished(void) const
{
	return _finished;
}
