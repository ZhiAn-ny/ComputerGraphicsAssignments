#ifndef GAME_RESOURCES_H_
#define GAME_RESOURCES_H_

#include "lib.h"

namespace res
{
	namespace color
	{
		const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
		const vec4 white = vec4(1.0, 1.0, 1.0, 1.0);

		const vec4 red = vec4(1.0, 0.0, 0.0, 1.0);
		const vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
		const vec4 blue = vec4(0.0, 0.0, 1.0, 1.0);
		const vec4 cyan = vec4(0.0, 1.0, 1.0, 1.0);
		const vec4 yellow = vec4(1.0, 1.0, 0.0, 1.0);
		const vec4 magenta = vec4(1.0, 0.0, 1.0, 1.0);

		const vec4 coral = vec4(1.0, 0.5, 0.31, 1.0);

	} // !color

	namespace mat
	{
		typedef struct Material {
			vec3 ambient;
			vec3 diffuse;
			vec3 specular;
			float shininess;
		};

		const Material tutorial = { vec3(1.0f, 0.5f, 0.31f),
			vec3(1.0f, 0.5f, 0.31f), vec3(0.5f, 0.5f, 0.5f), 32.0f };

		const Material jade = { vec3(0.135, 0.2225, 0.1575),
			vec3(0.54, 0.89, 0.63), vec3(0.316228, 0.316228, 0.316228), 0.1};

		const Material gold = { vec3(0.24725, 0.1995, 0.0745),
			vec3(0.75164, 0.60648, 0.22648), vec3(0.628281, 0.555802, 0.366065),
			0.4};

	} // !mat

} // !res

#endif // !GAME_RESOURCES_H_
