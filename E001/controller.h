#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "Lib.h"
#include "shape_factory.h"
#include "scene.h"

namespace gctrl {

	enum class GameAction {
		kFire,
		kMoveDragonUp,
		kMoveDragonDown,
		kAddEnemy
	};

	class GameController {
	private:
		RECT window = {};
		gsf::ShapeFactory shape_factory = gsf::ShapeFactory();
		gscene::Scene* scene_ = {};

		bool is_outside_window(gso::SceneObject* fig);

		void check_collisions();

		void move_dragon(gso::Direction dir);

		void update_fireballs();

		void add_enemy(glm::vec2 pos);

		void fire();

	public:

		GameController();
		~GameController();

		void init_game(gscene::Scene* scene);

		void action(GameAction action, glm::vec2 pos);

		void set_window(RECT window);

		void game_loop();

	};

}

#endif // !GAME_CONTROLLER_H_
