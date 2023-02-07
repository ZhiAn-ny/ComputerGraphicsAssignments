#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "lib.h"
#include "scene3d.h"
#include "camera.h"

using namespace gobj;
using namespace gview::gcam;

namespace gctrl
{
	enum MenuActions {
		deselect = 0,

		mat_tutorial = 1,
		mat_jade = 2,
		mat_gold = 3,
		mat_mtl = 4,

		sh_phong_phong = -1,
		sh_blinn_phong_phong = -2,
		sh_phong_interp= -3,
		sh_blinn_phong_interp= -4,
		sh_cartoon = -5,
		sh_texture = -6
	};

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
		void deselect_all();
		void change_selected_material(MenuActions type);
		void change_selected_shading(MenuActions type);
	};

} // !gctrl

#endif // !GAME_CONTROLLER_H_
