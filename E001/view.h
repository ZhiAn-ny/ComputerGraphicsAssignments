#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ShaderMaker.h"
#include "lib.h"
#include "controller.h"
#include "shape_factory.h"

namespace gview {

	static gctrl::GameController controller = {};

	static float margin_bottom;
	static float margin_top;
	static float default_figure_ray;

	class GameView {

		static void draw_scene(void);
		static void time_refresh(int value);
		static void reshape(int w, int h);
		static void keyboard_handler(unsigned char key, int x, int y);

		void init_window(const char* name);
		void create_scene_objects();
		void set_first_scene();

	public:
		GameView();
		~GameView();

		void init_view();

	};

}

#endif // !GAME_VIEW_H_
