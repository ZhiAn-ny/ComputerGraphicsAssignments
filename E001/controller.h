#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Lib.h"
#include "scene_object.h"
#include "scene.h"

namespace gctrl {

	class GameController {
	private:
		gscene::Scene* scene_ = {};

	public:
		GameController();
		~GameController();

		void init_game(gscene::Scene* scene);

		void game_loop();

	};

}

#endif // !GAME_CONTROLLER_H_
