#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ShaderMaker.h"
#include "lib.h"
#include "shape_factory.h"
#include "scene.h"

namespace gview {

	static float margin_bottom;
	static float margin_top;
	static float default_figure_ray;

	class GameView {
		RECT window_ = {};

		static void draw_scene(void);
		static void time_refresh(int value);

		void init_window(const char* name);
		void create_scene_objects();
		void set_first_scene();

	public:
		GameView();
		~GameView();

		void init_view();
		gscene::Scene* get_obj_layer_scene();

	};

}

#endif // !GAME_VIEW_H_
