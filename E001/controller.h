#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include <iostream>

#include "Lib.h"
#include "logic.h"
#include "shape_factory.h"
#include "actors.h"

namespace gctrl {

	enum class GameAction {
		kDoNothing,
		kFire,
		kMoveDragonUp,
		kMoveDragonDown,
		kAddEnemy,
		kIncreaseDragonSpeed,
		kDecreaseDragonSpeed,
	};

	class GameController {
	private:
		glog::GameLogic logic_ = glog::GameLogic();
		RECT window_ = {};
		gsf::ShapeFactory shape_factory = gsf::ShapeFactory();
		gscene::Scene* scene_ = {};

		bool is_outside_window(gso::SceneObject* fig);

		void check_collisions();

		void move_dragon(gso::Direction dir);

		void flap_wing();

		void update_fireballs();

		void update_butterflies();

		void replenish_butterflies();

		void remove_out_of_sight();

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
