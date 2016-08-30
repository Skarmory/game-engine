#ifndef render_system_h
#define render_system_h

#include <vector>
#include <memory>
#include <algorithm>

#include "libtcod.hpp"

#include "system.h"
#include "graphic_component.h"
#include "location_component.h"

using namespace std;

class RenderSystem : public System {
public:
	virtual void update(void) override;

private:
	static bool layer_compare(const weak_ptr<Entity>&, const weak_ptr<Entity>&);
	void clean(void);
};

#endif
