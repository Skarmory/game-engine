#ifndef sov_math_h
#define sov_math_h

#ifndef INFINITY
// Just in case
#define INFINITY ((float)(1e+300 * 1e+300))
#endif

#include <SFML\Graphics.hpp>

const sf::Vector2f world_up(0.f, -1.0f);
const sf::Vector2f world_right(1.f, 0.f);

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
float dot(const sf::Vector2f& v1);

sf::Vector2f normalise(const sf::Vector2f& v1);

float deg2rad(float degrees);
float rad2deg(float rads);

#endif
