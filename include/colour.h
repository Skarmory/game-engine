#ifndef colour_h
#define colour_h

#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <algorithm>

#include "util.h"

using namespace sf;

struct HSV {
	float hue, saturation, value;
};

void set_hue(Color& colour, float hue);
void set_saturation(Color& colour, float saturation);
void set_value(Color& colour, float value);
void set_hsv(Color& colour, float hue, float saturation, float value);

float get_hue(const Color& colour);
float get_saturation(const Color& colour);
float get_value(const Color& colour);
HSV   get_hsv(const Color& colour);

void lerp_colour_map(Color* map, const Color& from, const Color& to, int intervals);

static const Color Fuchsia(255, 0, 255);
static const Color Flame(226, 88, 34);
static const Color Pink(255, 192, 203);
static const Color Amber(255, 191, 0);
static const Color Orange(255, 128, 0);
static const Color Gold(255, 215, 0);
static const Color Chartreuse(127, 255, 0);
static const Color Teal(0, 128, 128);
static const Color Turquoise(64, 224, 208);
static const Color Azure(0, 127, 255);
static const Color Sky(135, 206, 235);
static const Color Purple(128, 0, 128);
static const Color Violet(127, 0, 255);
static const Color Amethyst(153, 102, 204);
static const Color Silver(192, 192, 192);
static const Color Brown(150, 75, 0);
#endif
