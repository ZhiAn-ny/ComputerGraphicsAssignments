#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ShaderMaker.h"
#include "lib.h"
#include "ShapeFactory.h"
#include "Scene.h"

namespace gview {

	class GameView {


	public:
		GameView();
		~GameView();

		void init_view();

	};

	void createWindow(const char* name);

	void INIT_VAO();

	void drawScene(void);

	void timeRefresh(int value);
}

#endif // !GAME_VIEW_H_
