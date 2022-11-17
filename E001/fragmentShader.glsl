#version 420 core

uniform float time;
uniform vec2 resolution;
uniform unsigned int isBackground;

// Background color
//vec3 color = vec3((243.0/255.0), (234.0/255.0), (191.0/255.0)); // sand
vec3 color = vec3((183.0/255.0), (206.0/255.0), (220.0/255.0)); // light_blue_gray

const vec3 water_base_color = vec3((31.0/255.0), (38.0/255.0), (64.0/255.0));

// Interpolated values from the vertex shaders
in vec4 ourColor;
out vec4 FragColor;  

float noise(float x, float amplitude)
{
	float n = 0.05 * sin(x * 8.0 + time) 
			+ 0.005 * sin(x * 27.3 + 0.5 * time) 
			+ 0.01 * sin(time);
	return n * amplitude;
}

// Convert fragment coordinates to normalized device coordinates
vec2 convert_to_ndc()
{
	return vec2(
		2 * (gl_FragCoord.x / resolution.x - 0.5),
		2 * (gl_FragCoord.y / resolution.y - 0.5)
	);
}

float calculate_alpha(vec2 ndc)
{
	// Build frequency components of the sinusoidal noise
	float n0 = noise(ndc.x * 3.18, 0.3);
	float n1 = noise(ndc.x * 2.34, 0.4);
	float n2 = noise(ndc.x * 2.14, 0.6);
	float n3 = noise(ndc.x * 1.40, 0.8);
	float n4 = noise(ndc.x * 1.23, 1.0);

	// Determine color based on distance from bottom
	if (ndc.y < -0.8 - n4)
		return 0.9; // 1st from bottom

	if (ndc.y < -0.6 - n3)
		return 0.7; // 2nd from bottom

	if (ndc.y < -0.4 - n2)
		return 0.5; // 3rd from bottom

	if (ndc.y < -0.2 - n1)
		return 0.3; // 2nd from top

	if (ndc.y < -n0)
		return 0.1; // 1st from top

	return 0.0; //bg upper (lightest)
}

void main()
{
	float alpha = 0.0;
	vec2 ndc = convert_to_ndc();

	if (isBackground == 0) {
		FragColor = ourColor;
		return;
	}

	// Render background
		alpha = calculate_alpha(ndc);

		if (alpha > 0.0) {
			color = mix(
				vec3(color.r, color.g, color.b),
				water_base_color,
				alpha
			);
		}

		FragColor = vec4(color, 1.0);

}
