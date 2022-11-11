#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "ShaderMaker.h"
#include "lib.h"
#include "ShapeFactory.h"
#include "Scene.h"
//#include "Mouse.h"

namespace gctrl {

	class GameController {


	public:
		GameController();
		~GameController();

		void init_game();

	};

	void createWindow(const char* name);

	void INIT_VAO();

	void drawScene(void);

	void timeRefresh(int value);

}

#endif // !GAME_CONTROLLER_H_
