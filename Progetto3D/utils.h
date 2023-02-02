#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "lib.h"
#include "amesh.h"

namespace util
{
	unsigned int check_error(string message);
	bool is_in_range(double a, double b, double x);
	vec3 distance(vec3 a, vec3 b);

	const int mouse_wheel_up = 4;
	const int mouse_wheel_down = 3;

	namespace dir {
		enum class Directions {
			front,
			back,
			up,
			down,
			left,
			right
		};

	} // !dir

} // !util

#endif // !GAME_UTILS_H_
