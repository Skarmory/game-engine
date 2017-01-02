#ifndef game_time_h
#define game_time_h

#include <chrono>

using namespace std;
using namespace std::chrono;

class GameTime 
{
public:
	GameTime(void) : _current(high_resolution_clock::now()), _previous(high_resolution_clock::now()) {}

	void tick(void);
	double delta(void) const;

private:
	time_point<high_resolution_clock> _current;
	time_point<high_resolution_clock> _previous;
	duration<double> _delta;
};

class Timer
{
public:
	explicit Timer(double duration) : _elapsed(0), _count_to(duration), _finished(false) {}

	void tick(const GameTime&);
	void reset(void);
	double time_elapsed(void) const;
	bool finished(void) const;

private:
	duration<double> _elapsed;
	duration<double> _count_to;
	bool _finished;
};

#endif
