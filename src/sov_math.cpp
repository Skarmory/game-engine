#define _USE_MATH_DEFINES

#include "sov_math.h"

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

bool line_line_intersect(const Line& line1, const Line& line2, float& scalar)
{
	float determinant = line2.direction.x * line1.direction.y - line2.direction.y * line1.direction.x;

	if (determinant == 0.0f)
		return false;

	float line2_scalar = (line1.direction.x * (line2.origin.y - line1.origin.y) + line1.direction.y * (line1.origin.x - line2.origin.x)) / determinant;

	if (line2_scalar < 0.0f || line2_scalar > 1.0f)
		return false;

	float line1_scalar = (line2.origin.x + (line2.direction.x * line2_scalar) - line1.origin.x) / line1.direction.x;

	if (line1_scalar <= 0.0f)
		return false;


	scalar = line1_scalar;

	return true;
}

bool line_rect_intersect(const Line& line, const sf::Vector2f& rect_centre, float& xsect1, float& xsect2, int& xsect_amount)
{
	// Corners of the square
	sf::Vector2f tl = rect_centre + sf::Vector2f(-16.f, -16.f);
	sf::Vector2f tr = rect_centre + sf::Vector2f(16.f, -16.f);
	sf::Vector2f bl = rect_centre + sf::Vector2f(-16.f, 16.f);
	sf::Vector2f br = rect_centre + sf::Vector2f(16.f, 16.f);

	// Lines of the rect in parametric form (u + tv)
	Line top(tl, tr - tl);
	Line right(tr, br - tr);
	Line left(tl, bl - tl);
	Line bottom(bl, br - bl);

	float top_s, bot_s, left_s, right_s;
	xsect1 = INFINITY;
	xsect2 = INFINITY;
	xsect_amount = 0;

	// Top line intersect
	if (line_line_intersect(line, top, top_s))
	{
		// Because this is the first to be evaluated we can just set it regardless
		xsect1 = top_s;
	}

	// Left line intersect
	if (line_line_intersect(line, left, left_s))
	{
		if (left_s < xsect1)
		{
			xsect2 = xsect1;
			xsect1 = left_s;
		}
		else if (left_s < xsect2)
		{
			xsect2 = left_s;
		}
	}

	// Right line intersect
	if (line_line_intersect(line, right, right_s))
	{
		if (right_s < xsect1)
		{
			xsect2 = xsect1;
			xsect1 = right_s;
		}
		else if (right_s < xsect2)
		{
			xsect2 = right_s;
		}
	}
	
	// Bottom line intersect
	if (line_line_intersect(line, bottom, bot_s))
	{
		if (bot_s < xsect1)
		{
			xsect2 = xsect1;
			xsect1 = bot_s;
		}
		else if (bot_s < xsect2)
		{
			xsect2 = bot_s;
		}
	}

	if (xsect1 == INFINITY && xsect2 == INFINITY)
		return false;

	if (xsect1 == xsect2)
	{
		xsect_amount++;
		return true;
	}

	if (xsect1 < INFINITY)
		xsect_amount++;

	if (xsect2 < INFINITY)
		xsect_amount++;

	return true;
}