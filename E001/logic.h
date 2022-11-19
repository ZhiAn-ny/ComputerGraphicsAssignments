#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include <iostream>

#include "scene.h"

namespace glog {

	class GameLogic {
	private:
		RECT world_boundary_ = {};
		gscene::Scene* scene_ = {};
		const int n_butterflies_ = 3;
		double score_ = 0.0;

		void add_score(double points);

	public:
		GameLogic();
		~GameLogic();

		int get_min_butterflies();

		double get_score();

		// Check if scene object respects wold's boundaries
		bool can_move(std::string name, gso::Direction dir);

		void kill(std::string name);

		void init_logic(gscene::Scene* scene);

		void set_world_boundaries(RECT window);
	};

}

#endif // !GAME_LOGIC_H_
