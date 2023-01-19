#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "lib.h"

namespace util
{
	unsigned int check_error(string message);

	namespace dir {
		enum class Directions {
			front,
			back,
			up,
			down,
			left,
			right
		};

		const vec3 front = vec3(0.0f, 0.0f, -1.0f);
		const vec3 back = vec3(0.0f, 0.0f, 1.0f);
		const vec3 up = vec3(0.0f, 1.0f, 0.0f);
		const vec3 down = vec3(0.0f, -1.0f, 0.0f);
		const vec3 left = vec3(-1.0f, 0.0f, 0.0f);
		const vec3 right = vec3(1.0f, 0.0f, 0.0f);
		
	} // !dir

} // !util

#endif // !GAME_UTILS_H_
