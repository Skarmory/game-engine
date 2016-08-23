#ifndef graphic_component_h
#define graphic_component_h

#include "component.h"
#include "libtcod.hpp"

struct GraphicComponent : public Component
{
	GraphicComponent(char graphic, TCODColor colour);
	~GraphicComponent(void);

	char graphic;
	TCODColor colour;
};

#endif
