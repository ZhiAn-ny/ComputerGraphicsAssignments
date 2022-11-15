#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Lib.h"
#include "scene_object.h"
#include "scene.h"

namespace gctrl {

	enum class GameAction {
		kFire,
		kMoveUp,
		kMoveDown
	};

	class GameController {
	private:
		gscene::Scene* scene_ = {};

	public:
		GameController();
		~GameController();

		void init_game(gscene::Scene* scene);

		void action(GameAction action);

		// TODO:
		void game_loop();

	};

}

#endif // !GAME_CONTROLLER_H_
