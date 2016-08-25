#include "graphic_component.h"

GraphicComponent::GraphicComponent(char graphic, TCODColor colour, DrawLayer layer) : Component("GraphicComponent"), graphic(graphic), colour(colour), layer(layer)  
{}

