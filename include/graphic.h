#ifndef graphic_component_h
#define graphic_component_h

#include <SFML\Graphics.hpp>

#include "component.h"

namespace sov
{
	enum DrawLayer
	{
		EFFECT = 0,
		OBJECT = 1,
		ITEM = 2,
		CREATURE = 3
	};

	struct Graphic : public Component<Graphic>
	{
		Graphic(void) {}
		Graphic(sf::Sprite sprite, sf::Transform sprite_transform, DrawLayer layer) : sprite(sprite), layer(layer) {}

		sf::Sprite sprite;
		sf::Transform sprite_transform;
		float brightness;
		DrawLayer layer;
	};
};

#endif
