#ifndef render_system_h
#define render_system_h

#include <vector>

#include "libtcod.hpp"

#include <memory>
#include "system.h"
#include "graphic_component.h"
#include "location_component.h"

class RenderSystem : public System {
public:
	RenderSystem(void) {};
	~RenderSystem(void) {};

	virtual void update(void) override;
};

#endif
