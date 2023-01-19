#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "lib.h"

namespace util
{
	unsigned int check_error(string message);

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

		const string ambient_light = "ambientLight";
		const string ambient_light_pwr = "ambientLight_pwr";

	} // !uvar

} // !util

#endif // !GAME_UTILS_H_
