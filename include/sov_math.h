#ifndef sov_math_h
#define sov_math_h

#ifndef INFINITY
// Just in case
#define INFINITY ((float)(1e+300 * 1e+300))
#endif

#include <set>
#include <SFML\Graphics.hpp>

const sf::Vector2f world_up(0.f, -1.0f);
const sf::Vector2f world_right(1.f, 0.f);

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
float dot(const sf::Vector2f& v1);

sf::Vector2f normalise(const sf::Vector2f& v1);

// Angles

float deg2rad(float degrees);
float rad2deg(float rads);

// Parametric lines

//struct LineIntersectScalars
//{
//	float line1_scalar;
//	float line2_scalar;
//};

struct Line
{
	Line(void) : origin(0.f, 0.f), direction(1.f, 0.f) {}
	Line(sf::Vector2f origin, sf::Vector2f direction) : origin(origin), direction(direction) {}

	sf::Vector2f origin;
	sf::Vector2f direction;
};

bool line_line_intersect(const Line& line1, const Line& line2, float& scalar);
bool line_rect_intersect(const Line& line, const sf::Vector2f& rect_centre, float& xsect1, float& xsect2, int& xsect_amount);

#endif
