#ifndef graphic_component_h
#define graphic_component_h

#include "component.h"

class GraphicComponent : public Component
{
public:
	GraphicComponent(char graphic);
	~GraphicComponent(void);

	char graphic(void) const { return _graphic; }

private:
	char _graphic;
};

#endif
