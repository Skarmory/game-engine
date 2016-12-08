#ifndef render_system_h
#define render_system_h

#include <vector>
#include <memory>
#include <algorithm>

#include "system.h"
#include "components.h"
#include "events.h"
#include "level.h"
#include "light_system.h"
#include "visibility_system.h"
#include "colour.h"
#include "ui.h"

using namespace std;
using namespace sov;

class Camera;

class RenderSystem : public System, public Observer<EntityCreated> {
public:
	RenderSystem(const SystemManager& sm, Level* level, const Camera& camera) : System(sm), _level(level), _camera(camera) {}

	virtual void init(EventManager& evm) override;
	virtual void update(EventManager& evm) override;
	virtual void receive(const EntityCreated& e) override;

	const Map<sov::Glyph>& get_composed_map(void) const;

private:
	static bool layer_compare(const weak_ptr<Entity>&, const weak_ptr<Entity>&);
	void clean(void);

	void map_drawable_entities(void);
	void map_base_terrain(void);

	const Camera& _camera;
	Level*  _level;
	Map<sov::Glyph> _composed_map;
};

#endif
