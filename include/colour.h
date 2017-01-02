#ifndef colour_h
#define colour_h

#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <algorithm>
#include <map>
#include <string>

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

// All the colours in the world 

static const Color DarkRed(191, 0, 0);
static const Color LightRed(255, 115, 115);

static const Color DarkFlame(191, 47, 0);
static const Color Flame(225, 63, 0);
static const Color LightFlame(225, 185, 115);

static const Color DarkOrange(191, 95, 0);
static const Color Orange(255, 128, 0);
static const Color LightOrange(255, 185, 115);

static const Color DarkAmber(191, 143, 0);
static const Color Amber(255, 191, 0);
static const Color LightAmber(255, 220, 115);

static const Color DarkYellow(191, 191, 0);
static const Color LightYellow(255, 255, 115);

static const Color DarkChartreuse(95, 191, 0);
static const Color Chartreuse(127, 255, 0);
static const Color LightChartreuse(185, 255, 115);

static const Color DarkGreen(0, 191, 0);
static const Color LightGreen(115, 255, 115);

static const Color DarkTeal(0, 95, 95);
static const Color Teal(0, 128, 128);
static const Color LightTeal(0, 185, 185);

static const Color DarkTurquoise(0, 191, 143);
static const Color Turquoise(0, 225, 191);
static const Color LightTurquoise(115, 255, 220);

static const Color DarkCyan(0, 191, 191);
static const Color LightCyan(115, 255, 255);

static const Color DarkSkyBlue(0, 143, 191);
static const Color SkyBlue(0, 191, 255);
static const Color LightSkyBlue(115, 220, 255);

static const Color DarkAzure(0, 95, 191);
static const Color Azure(0, 127, 255);
static const Color LightAzure(115, 185, 255);

static const Color DarkBlue(0, 0, 255);
static const Color LightBlue(115, 115, 255);

static const Color DarkVioletBlue(47, 0, 191);
static const Color VioletBlue(63, 0, 255);
static const Color LightVioletBlue(149, 115, 255);

static const Color DarkViolet(95, 0, 191);
static const Color Violet(127, 0, 255);
static const Color LightViolet(185, 115, 255);

static const Color DarkPurple(143, 0, 191);
static const Color Purple(191, 0, 128);
static const Color LightPurple(220, 115, 255);

static const Color DarkFuchsia(191, 0, 191);
static const Color Fuchsia(255, 0, 255);
static const Color LightFuchsia(255, 115, 255);

static const Color DarkMagenta(191, 0, 143);
static const Color LightMagenta(255, 155, 220);

static const Color DarkPink(191, 0, 95);
static const Color Pink(255, 0, 127);
static const Color LightPink(255, 115, 185);

static const Color Brown(150, 75, 0);

static const Color Silver(192, 192, 192);
static const Color Gold(255, 215, 0);

static const std::map<const std::string, const Color&> colours_map = {
	{ "transparent", Color::Transparent },
	{ "dark_red", DarkRed },{ "red", Color::Red },{ "light_red", LightRed },
	{ "dark_flame", DarkFlame },{ "flame", Flame },{ "light_flame", LightFlame },
	{ "dark_orange", DarkOrange },{ "orange", Orange },{ "light_orange", LightOrange },
	{ "dark_amber", DarkAmber },{ "amber", Amber },{ "light_amber", LightAmber },
	{ "dark_yellow", DarkYellow },{ "yellow", Color::Yellow },{ "light_yellow", LightYellow },
	{ "dark_chartreuse", DarkChartreuse },{ "chartreuse", Chartreuse },{ "light_chartreuse", LightChartreuse },
	{ "dark_green", DarkGreen }, { "green", Color::Green }, { "light_green", LightGreen},
	{ "dark_teal", DarkTeal },{ "teal", Teal },{ "light_teal", LightTeal },
	{ "dark_turquoise", DarkTurquoise },{ "turquoise", Turquoise },{ "light_turquoise", LightTurquoise },
	{ "dark_cyan", DarkCyan },{ "cyan", Color::Cyan },{ "light_cyan", LightCyan },
	{ "dark_skyblue", DarkSkyBlue },{ "skyblue", SkyBlue },{ "light_skyblue", LightSkyBlue },
	{ "dark_azure", DarkAzure },{ "azure", Azure },{ "light_azure", LightAzure },
	{ "dark_blue", DarkBlue },{ "blue", Color::Blue },{ "light_blue", LightBlue },
	{ "dark_violetblue", DarkVioletBlue },{ "violetblue", VioletBlue },{ "light_violetblue", LightVioletBlue },
	{ "dark_violet", DarkViolet },{ "violet", Violet },{ "light_violet", LightViolet },
	{ "dark_purple", DarkPurple },{ "purple", Purple },{ "light_purple", LightPurple },
	{ "dark_fuchsia", DarkFuchsia },{ "fuchsia", Fuchsia },{ "light_fuchsia", LightFuchsia },
	{ "dark_magenta", DarkMagenta },{ "magenta", Color::Magenta },{ "light_magenta", LightMagenta },
	{ "dark_pink", DarkPink },{ "pink", Pink },{ "light_pink", LightPink },
	{ "brown", Brown },
	{ "silver", Silver },
	{ "gold", Gold },
	{ "white", Color::White },
	{ "black", Color::Black }
};

#endif
