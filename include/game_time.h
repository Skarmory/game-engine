#ifndef game_time_h
#define game_time_h

#include <chrono>

class GameTime 
{
public:
	GameTime(void) : _current(std::chrono::high_resolution_clock::now()), _previous(std::chrono::high_resolution_clock::now()) {}

	void tick(void);
	double delta(void) const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _current;
	std::chrono::time_point<std::chrono::high_resolution_clock> _previous;
	std::chrono::duration<double> _delta;
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
	std::chrono::duration<double> _elapsed;
	std::chrono::duration<double> _count_to;
	bool _finished;
};

#endif
