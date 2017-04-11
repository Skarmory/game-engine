#ifndef render_system_h
#define render_system_h

#include <memory>

#include "system.h"
#include "events.h"
#include "ui.h"
#include "map.h"

class RenderSystem : public System, public sov::Observer<EntityCreated>
{

public:
	RenderSystem(Viewport& viewport) : _viewport(viewport) {}

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& e) override;

private:

	const int SPRITE_WIDTH = 32;
	const int SPRITE_HEIGHT = 32;
	const int SPRITE_SHEET_WIDTH = 16;
	const int SPRITE_SHEET_HEIGHT = 16;

	static bool layer_compare(const weak_ptr<Entity>&, const weak_ptr<Entity>&);
	void _clean(void);

	void _map_drawable_entities(void);
	void _map_base_terrain(void);

	Viewport& _viewport;
	sf::RenderTexture _rtex;
};

#endif
