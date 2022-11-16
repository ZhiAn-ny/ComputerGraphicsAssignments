#version 420 core

uniform float time;
uniform vec2 resolution;
uniform unsigned int isBackground;

const vec3 water_base_color = vec3(0.2, 0.1, 1.0);
vec3 color = vec3(1.0);

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

float calculate_v(vec2 ndc)
{
	// Build frequency components of the sinusoidal noise
	float n0 = noise(ndc.x * 3.18, 0.3);
	float n1 = noise(ndc.x * 2.34, 0.4);
	float n2 = noise(ndc.x * 2.14, 0.6);
	float n3 = noise(ndc.x * 1.40, 0.8);
	float n4 = noise(ndc.x * 1.23, 1.0);

	// Determine color based on distance from bottom
	if (ndc.y < -0.8 - n4)
		return 1.0;

	if (ndc.y < -0.6 - n3)
		return 0.8;

	if (ndc.y < -0.4 - n2)
		return 0.6;

	if (ndc.y < -0.2 - n1)
		return 0.4;

	if (ndc.y < -n0)
		return 0.3;

	return 0.0;
}

void main()
{
	float v = 0.0;
	vec2 ndc = convert_to_ndc();

	if (isBackground == 0) {
		FragColor = ourColor;
		return;
	}

	// Refer to bottom half of the window
	if (ndc.y > -1 && ndc.y < 0) {
		v = calculate_v(ndc);

		if (v > 0.0) {
			vec3 water_color = water_base_color * v;
			color = mix(
				vec3(ourColor.r, ourColor.g, ourColor.b),
				water_color,
				0.8
			);
		}

		FragColor = vec4(color, 1.0);

	} else { // !(ndc.y > -1 && ndc.y < 0)

		// Referring to upper half of the window
		// Assign to each fragment the interpolated color
		FragColor = ourColor;
	}
}
