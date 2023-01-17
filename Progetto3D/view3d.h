#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include "shader.h"
#include "scene3d.h"
#include "mesh_factory.h"

using namespace gobj;

namespace gview
{

	class GameView3D {
	private:

		static void draw_scene(void);
		static void time_refresh(int a);
		static void resize(int w, int h);

		void create_window(const char* title);
		void set_scene();
		void set_camera();

	public:
		GameView3D();
		~GameView3D();

		void init();
		void start();
	};

} // !gview

#endif // !GAME_VIEW_H_