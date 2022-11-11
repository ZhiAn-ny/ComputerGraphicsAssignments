#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "view.h"

namespace gctrl {

	class GameController {
	private:
		gview::GameView view = gview::GameView();

	public:
		GameController();
		~GameController();

		void init_game();

	};

}

#endif // !GAME_CONTROLLER_H_
