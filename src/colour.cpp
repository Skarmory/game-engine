#include "colour.h"

// RGB <-> HSV conversions

float get_hue(const Color& colour)
{
	int max = std::max(colour.r, std::max(colour.g, colour.b));
	int min = std::min(colour.r, std::min(colour.g, colour.b));
	float delta = (float)max - (float)min;
	float ret;

	if (delta == 0.0f)
	{
		ret = 0.0f;
	}
	else 
	{
		if (colour.r == max) 
			ret = (float)(colour.g - colour.b) / delta;
		else if (colour.g == max) 
			ret = 2.0f + (float)(colour.b - colour.r) / delta;
		else 
			ret = 4.0f + (float)(colour.r - colour.g) / delta;

		ret *= 60.0f;
		if (ret < 0.0f) 
			ret += 360.0f;

		if (ret >= 360.0f) 
			ret -= 360.0f;
	}

	return ret;
}

float get_saturation(const Color& colour)
{
	float max = (float)(std::max(colour.r, std::max(colour.g, colour.b))) / 255.0f;
	float min = (float)(std::min(colour.r, std::min(colour.g, colour.b))) / 255.0f;
	float delta = max - min;

	if (max == 0.0f) 
		return 0.0f;
	else 
		return delta / max;
}

float get_value(const Color& colour)
{
	return (float)(std::max(colour.r, std::max(colour.g, colour.b))) / 255.0f;
}

HSV get_hsv(const Color& colour) 
{
	HSV ret;
	ret.hue = get_hue(colour);
	ret.saturation = get_saturation(colour);
	ret.value = get_value(colour);

	return ret;
}


void set_hue(Color& colour, float hue)
{
	HSV tmp = get_hsv(colour);
	set_hsv(colour, hue, tmp.saturation, tmp.value);
}

void set_saturation(Color& colour, float saturation)
{
	HSV tmp = get_hsv(colour);
	set_hsv(colour, tmp.hue, saturation, tmp.value);
}

void set_value(Color& colour, float value)
{
	HSV tmp = get_hsv(colour);
	set_hsv(colour, tmp.hue, tmp.saturation, value);
}

void set_hsv(Color& colour, float hue, float saturation, float value)
{
	int i;
	float f, p, q, t;

	if (saturation == 0.0f)
	{
		colour.r = colour.g = colour.b = (int)(value * 255.0f + 0.5f);
		return;
	}

	while (hue < 0.0f)
		hue += 360.0f;

	while (hue >= 360.0f)
		hue -= 360.0f;

	hue /= 60.f;

	i = (int)floor(hue);
	f = hue - i;
	p = value * (1 - saturation);
	q = value * (1 - saturation * f);
	t = value * (1 - saturation * (1 - f));

	switch (i)
	{
	case 0:
		colour.r = (int)(value * 255.0f + 0.5f);
		colour.g = (int)(t * 255.0f + 0.5f);
		colour.b = (int)(p * 255.0f + 0.5f);
		break;

	case 1:
		colour.r = (int)(q * 255.0f + 0.5f);
		colour.g = (int)(value * 255.0f + 0.5f);
		colour.b = (int)(p * 255.0f + 0.5f);
		break;

	case 2:
		colour.r = (int)(p * 255.0f + 0.5f);
		colour.g = (int)(value * 255.0f + 0.5f);
		colour.b = (int)(t * 255.0f + 0.5f);
		break;

	case 3:
		colour.r = (int)(p * 255.0f + 0.5f);
		colour.g = (int)(q * 255.0f + 0.5f);
		colour.b = (int)(value * 255.0f + 0.5f);
		break;

	case 4:
		colour.r = (int)(t * 255.0f + 0.5f);
		colour.g = (int)(p * 255.0f + 0.5f);
		colour.b = (int)(value * 255.0f + 0.5f);
		break;

	default:
		colour.r = (int)(value * 255.0f + 0.5f);
		colour.g = (int)(p * 255.0f + 0.5f);
		colour.b = (int)(q * 255.0f + 0.5f);
		break;
	}
}

// Other functions

void lerp_colour_map(Color* map, const Color& from, const Color& to, int steps)
{	
	float f_h = get_hue(from);
	float f_s = get_saturation(from);
	float f_v = get_value(from);

	float t_h = get_hue(to);
	float t_s = get_saturation(to);
	float t_v = get_value(to);

	map[0] = from;

	for (int i = 1; i < steps; i++)
	{
		Color c(0,0,0);

		float h = interpolate_f(f_h, t_h, i, steps);
		float s = interpolate_f(f_s, t_s, i, steps);
		float v = interpolate_f(f_v, t_v, i, steps);

		set_hsv(c, h, s, v);
		map[i] = c;
	}
}