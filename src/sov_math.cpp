#include "sov_math.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <math.h>

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float dot(const sf::Vector2f& v1)
{
	return (v1.x * v1.x) + (v1.y * v1.y);
}

sf::Vector2f normalise(const sf::Vector2f& v1)
{
	float l = std::sqrt(dot(v1));
	return sf::Vector2f(v1.x / l, v1.y / l);
}

float deg2rad(float degrees)
{
	return degrees * M_PI / 180.f;
}

float rad2deg(float rads)
{
	return rads * 180.f / M_PI;
}