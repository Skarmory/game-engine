#ifndef util_h
#define util_h

//#include <random>

//extern mt19937 rng;

template <typename T>
T clamp(T low, T high, T value)
{
	if (value < low)
		return low;
	else if (value > high)
		return high;
	else
		return value;
}

float interpolate_f(float start, float end, int step, int last);

#endif
