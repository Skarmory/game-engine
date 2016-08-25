#ifndef graphic_component_h
#define graphic_component_h

#include "component.h"
#include "libtcod.hpp"

enum DrawLayer 
{
	EFFECT   = 0,
	OBJECT   = 1,
	ITEM     = 2,
	CREATURE = 3
};

struct GraphicComponent : public Component
{
	GraphicComponent(char graphic, TCODColor colour, DrawLayer layer);

	char 	  graphic;
	TCODColor colour;
	DrawLayer layer;
};

#endif
