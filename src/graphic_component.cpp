#include "graphic_component.h"

GraphicComponent::GraphicComponent(char graphic, TCODColor fg_colour, TCODColor bg_colour, DrawLayer layer) : 
	Component("GraphicComponent"), graphic(graphic), fg_colour(fg_colour), bg_colour(bg_colour), layer(layer)  
{}

