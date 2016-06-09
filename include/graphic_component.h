#ifndef graphic_component_h
#define graphic_component_h

#include "component.h"

struct GraphicComponent : public Component
{
	GraphicComponent(char graphic);
	~GraphicComponent(void);

	char graphic;
};

#endif
