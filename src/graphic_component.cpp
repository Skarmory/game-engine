#include "graphic_component.h"

GraphicComponent::GraphicComponent(char graphic, TCODColor colour) : Component("GraphicComponent"), graphic(graphic), colour(colour)  
{
}

GraphicComponent::~GraphicComponent(void)
{
}
