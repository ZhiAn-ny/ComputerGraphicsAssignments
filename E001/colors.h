#ifndef GAME_COLORS_H_
#define GAME_COLORS_H_

#include "Lib.h"

namespace color {

	const glm::vec4 white = glm::vec4(1.0);
	const glm::vec4 black = glm::vec4(0.0, 0.0, 0.0, 1.0);
	const glm::vec4 transparent = glm::vec4(0.0);

	const glm::vec4 purple = glm::vec4(1.0, 0.0, 1.0, 1.0);
	const glm::vec4 red = glm::vec4(1.0, 0.0, 0.0, 1.0);
	const glm::vec4 yellow = glm::vec4(1.0, 1.0, 0.0, 1.0);
	const glm::vec4 green = glm::vec4(0.0, 1.0, 0.0, 1.0);
	const glm::vec4 cyan = glm::vec4(0.0, 1.0, 1.0, 1.0);
	const glm::vec4 blue = glm::vec4(0.0, 0.0, 1.0, 1.0);

	const glm::vec4 medium_green = glm::vec4(72 / 255.0, 129 / 255.0, 36 / 255.0, 1.0);
	const glm::vec4 dark_dreen = glm::vec4(17 / 255.0, 74 / 255.0, 39 / 255.0, 1.0);

	const glm::vec4 dark_yellow = glm::vec4(240 / 255.0, 211 / 255.0, 81 / 255.0, 1.0);
	const glm::vec4 dark_orange = glm::vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0);

}

#endif // !GAME_COLORS_H_
