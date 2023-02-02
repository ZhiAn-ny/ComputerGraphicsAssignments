#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "lib.h"
#include "scene3d.h"
#include "camera.h"

using namespace gobj;
using namespace gview::gcam;

namespace gctrl
{
	class GameController {
	private:
		Scene* scene_ = nullptr;
		RECT* win_ = nullptr;
		mat4* Projection_ = nullptr;
		Camera* cam_ = nullptr;

		vec3 get_ray(int x, int y);

	public:
		GameController();
		~GameController();

		void init(Scene* scene, RECT* window, mat4* proj, Camera* cam);
		void select_object(int x, int y);

	};

} // !gctrl

#endif // !GAME_CONTROLLER_H_
