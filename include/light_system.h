#ifndef light_system_h
#define light_system_h

#include "system.h"
#include "events.h"
#include "ui.h"

class LightSystem : public System, public sov::Observer<EntityCreated>
{
public:
	explicit LightSystem(Viewport* viewport) : _viewport(viewport) {}

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void receive(const EntityCreated& event) override;

	const sf::RenderTexture& get_lightmap(void) const;

private:

	const char* _light_vshader_src =
		"void main()"
		"{"
		"gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;"
		"gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;"
		"gl_FrontColor = gl_Color;"
		"}";

	const char* _light_fshader_src =
		"uniform vec4 colour;"
		"uniform vec2 centre;"
		"uniform float radius;"
		"uniform float window_height;"

		"void main(void)"
		"{"
		"vec2 centerFromSfml = vec2(centre.x, window_height - centre.y);"
		"float distance = length(centerFromSfml - gl_FragCoord.xy)/radius;"
		"gl_FragColor = mix(colour, gl_Color, distance);"
		"}";

	Viewport* _viewport;
	sf::RenderTexture _light_texture;
	sf::Shader _light_shader;
};

#endif
