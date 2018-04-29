uniform sampler2D tex;
uniform vec4 colour;
uniform vec2 centre;
uniform float radius;
uniform float height;
uniform float width;

void main(void)
{
	vec2 centre2 = vec2(centre.x, height - centre.y);
	float distance = length(centre2 - gl_FragCoord.xy) / radius;
	if(distance < 1.0)
	{
		vec4 col = vec4(1.0 - distance, 1.0 - distance, 1.0 - distance, 1.0);
		vec2 uv = vec2(gl_FragCoord.x / width, gl_FragCoord.y / height);
		vec4 pixel = texture2D(tex, uv);
		
		if(col.x > pixel.x)
		{
			gl_FragColor = col;
		}
		else
		{
			gl_FragColor = pixel;
		}
	}
	else
	{
		discard;
	}
}
