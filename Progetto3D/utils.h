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
		const string normalMatrix = "NormalMatrix";

		const string am_light = "ambient.color";
		const string am_light_pwr = "ambient.pwr";
		const string diff_light = "diffuse.color";
		const string diff_light_pwr = "diffuse.pwr";
		const string diff_light_pos = "diffuse.pos";

		const string cam_pos = "camPos";

	} // !uvar

} // !util

#endif // !GAME_UTILS_H_
