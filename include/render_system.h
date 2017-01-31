#ifndef render_system_h
#define render_system_h

#include <memory>

#include "system.h"
#include "events.h"
#include "ui.h"
#include "map.h"

class RenderSystem : public System, public sov::Observer<EntityCreated> {
public:
	RenderSystem(const Camera& camera) : _camera(camera) {}

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& e) override;

	const Map<sov::Glyph>& get_composed_map(void) const;

private:
	static bool layer_compare(const weak_ptr<Entity>&, const weak_ptr<Entity>&);
	void clean(void);

	void map_drawable_entities(void);
	void map_base_terrain(void);

	const Camera& _camera;
	Map<sov::Glyph> _composed_map;
};

#endif
