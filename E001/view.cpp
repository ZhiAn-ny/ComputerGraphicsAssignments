#include "view.h"

// GLOBAL VARIABLES

RECT window = {};
RECT window_update = {};

static unsigned int MatMod, MatProj, loctime, locres, isBackground;
glm::mat4 Projection;

gscene::Scene obj_layer;
gso::SceneObject bg = gso::SceneObject("bg");
//Mouse mouse;

/******************************************************************************/

gview::GameView::GameView() { }

gview::GameView::~GameView() { }

void gview::GameView::draw_scene(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Pass tme and resolution to fragment shader
	glUniform1f(loctime, glutGet(GLUT_ELAPSED_TIME) / 1000.0);
	glUniform2f(locres, window_update.right, window_update.bottom);

	glUniform1ui(isBackground, 1);
	bg.render(&MatMod);

	glUniform1ui(isBackground, 0);
	obj_layer.draw_scene(&MatMod, &MatProj, &Projection);

	glutSwapBuffers();
}

void gview::GameView::time_refresh(int value)
{
	float angolo = 0.0;
	float trasFactor;

	controller.game_loop();

	glutTimerFunc(50, time_refresh, 0);
	glutPostRedisplay();
}

void gview::GameView::reshape(int width, int height)
{
	// World ratio
	float ratio = (float)(window.right) / (float)(window.bottom);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int w = height * ratio;
	int left = (width - w) / 2;

	window_update.right = width;
	window_update.bottom = height;

	controller.set_window(window_update);

	glViewport(left, 0, w, height);
	gluOrtho2D(0, window.right, window.bottom, 0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void gview::GameView::keyboard_handler(unsigned char key, int x, int y)
{
	glm::vec2 null_position = glm::vec2(0);
	switch (key) {
	case ' ':
		controller.action(gctrl::GameAction::kFire, null_position);
		break;
	case 'w':
	case 'W':
		controller.action(gctrl::GameAction::kMoveDragonUp, null_position);
		break;
	case 's':
	case 'S':
		controller.action(gctrl::GameAction::kMoveDragonDown, null_position);
		break;
	}
	glutPostRedisplay();
}

void gview::GameView::mouse_handler(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		controller.action(gctrl::GameAction::kAddEnemy, glm::vec2(x,y));
	}
}

void gview::GameView::init_window(const char* name)
{
	int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	int INITIAL_POS = 50;

	window.right = SCREEN_WIDTH / 3 * 2;
	window.bottom = SCREEN_HEIGHT / 6 * 5;

	window_update = window;

	controller.set_window(window_update);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window.right, window.bottom);
	glutInitWindowPosition(INITIAL_POS, INITIAL_POS/2);
	glutCreateWindow((const char*)name);
}

void gview::GameView::create_dragon()
{
	gsf::ShapeFactory shf;
	gso::SceneObject shape;
	std::string name;

	{// Compose dragon
		glm::vec2 dragon_center = glm::vec2(window.right / 5, window.bottom / 2);

		shape = shf.get_dragon_tail();
		shape.set_color(color::dark_dreen, color::medium_green);
		shape.transform(glm::vec3(dragon_center.x - 100, dragon_center.y - 40, 0.0),
			glm::vec3(7), 0);
		obj_layer.add_object(&shape);

		shape = shf.get_dragon_body();
		shape.set_color(color::dark_dreen, color::medium_green);
		shape.transform(glm::vec3(dragon_center.x + 80, dragon_center.y, 0.0),
			glm::vec3(7), 0);
		obj_layer.add_object(&shape);

		shape = shf.get_dragon_wing();
		shape.set_color(color::dark_dreen, color::dark_yellow);
		shape.transform(glm::vec3(dragon_center.x + 30, dragon_center.y + 130, 0.0),
			glm::vec3(7), 0);
		obj_layer.add_object(&shape);

		shape = shf.get_dragon_head();
		shape.set_color(color::medium_green, color::dark_yellow);
		shape.transform(glm::vec3(dragon_center.x + 177, dragon_center.y + 30, 0.0),
			glm::vec3(7), 0);
		obj_layer.add_object(&shape);
	}
}

void gview::GameView::create_background()
{
	bg.add_vertex(glm::vec3(0), color::white);
	bg.add_vertex(glm::vec3(-1, 1, 0), color::white);
	bg.add_vertex(glm::vec3(1, 1, 0), color::white);
	bg.add_vertex(glm::vec3(1, -1, 0), color::white);
	bg.add_vertex(glm::vec3(-1, -1, 0), color::white);
	bg.add_vertex(glm::vec3(-1, 1, 0), color::white);

	bg.transform(
		glm::vec3(window.right / 2, window.bottom / 2, 0), 
		glm::vec3(window.right, window.bottom, 1), 
		0
	);

	bg.bind();
}

void gview::GameView::set_first_scene()
{
	this->create_dragon();
	
	this->create_background();

	// Pass uniform variables to the shader
	// Coordinates are specified in relation to the usage domain
	// (i.e. when dealing w/ temperature, the origin could be below zero)
	Projection = ortho(0.0f, float(window.right), 0.0f, float(window.bottom));
	MatProj = glGetUniformLocation(obj_layer.get_id(), "Projection");
	MatMod = glGetUniformLocation(obj_layer.get_id(), "Model");
	loctime = glGetUniformLocation(obj_layer.get_id(), "time");
	locres = glGetUniformLocation(obj_layer.get_id(), "resolution");
	isBackground = glGetUniformLocation(obj_layer.get_id(), "isBackground");
}

void gview::GameView::init_view()
{
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	this->init_window("my_game_app");

	controller = gctrl::GameController();
	controller.init_game(&obj_layer);
	controller.set_window(window);

	glutDisplayFunc(this->draw_scene);
	glutTimerFunc(50, this->time_refresh, 0);
	glutReshapeFunc(this->reshape);

	glutMouseFunc(this->mouse_handler);
	glutKeyboardFunc(this->keyboard_handler);

	glewExperimental = GL_TRUE;
	glewInit();

	obj_layer.set_shaders((char*)"vertexShader.glsl", (char*)"testFS.glsl");
	this->set_first_scene();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}
