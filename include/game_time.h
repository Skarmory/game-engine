#ifndef game_time_h
#define game_time_h

#include <chrono>

using namespace std;
using namespace std::chrono;

class GameTime 
{
	private:
		time_point<high_resolution_clock> _current;
		time_point<high_resolution_clock> _previous;
		duration<double> _delta;

	public:
		GameTime(void);

		void tick(void);

		double delta(void) const;
};

class Timer
{
	private:
		duration<double> _elapsed;
		duration<double> _count_to;
		bool _finished;

	public:
		Timer(double);

		void tick(const GameTime&);
		
		double time_elapsed(void) const;

		void reset(void);

		bool finished(void) const;
};

#endif
