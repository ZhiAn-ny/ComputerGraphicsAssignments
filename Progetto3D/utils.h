#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "lib.h"

namespace util
{
	unsigned int check_error(string message);

	const int max_n_lights = 10;

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

	// Defines the names of the uniform variables passed to the shaders.
	namespace uvar {
		const string model = "Model";
		const string view = "View";
		const string projection = "Projection";
		const string normalMatrix = "NormalMatrix";

		const string cam_pos = "camPos";


	} // !uvar

} // !util

#endif // !GAME_UTILS_H_
