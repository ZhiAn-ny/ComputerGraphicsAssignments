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
	} // !dir

} // !util

#endif // !GAME_UTILS_H_
