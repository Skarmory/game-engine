#include "util.h"

float interpolate_f(float start, float end, int step, int last)
{
	return (end - start) * ((float)step / (float)last) + start;
}