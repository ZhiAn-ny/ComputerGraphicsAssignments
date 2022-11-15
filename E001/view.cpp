#include "view.h"

// GLOBAL VARIABLES

RECT window = {};
RECT window_update = {};

static unsigned int MatMod, MatProj, locres;
mat4 Projection;

gscene::Scene obj_layer;
//Mouse mouse;

/******************************************************************************/

gview::GameView::GameView() { }

gview::GameView::~GameView() { }

void gview::GameView::draw_scene(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUniform2f(locres, window_update.right, window_update.bottom);

	obj_layer.draw_scene(&MatMod, &MatProj, &Projection);

	glutSwapBuffers();
}

void gview::GameView::time_refresh(int value)
{
	float angolo = 0.0;
	float trasFactor;
	//std::string moving = "butterfly_0";

	//std::string bottom = "butterfly_1";
	//std::string top = "butterfly_2";

	//gso::SceneObject* shape = obj_layer.get_object(moving);
	//gso::SceneObject* bshape = obj_layer.get_object(bottom);
	//gso::SceneObject* tshape = obj_layer.get_object(top);

	//gso::Direction dir = shape->get_direction();
	//glm::vec3 pos = shape->get_position();

	//// Change direction
	//if (shape->is_colliding(*bshape))
	//	shape->change_direction(gso::Direction::kUp);
	//if (shape->is_colliding(*tshape))
	//	shape->change_direction(gso::Direction::kDown);

	//shape->move(0.1);

	//gso::SceneObject* wing = obj_layer.get_object("wing");

	//float ratio = wing->get_width() / wing->get_height()

	//

	//wing->transform(glm::vec3(0.0), glm::vec3(1.0, 1.1, 1.0), 0.0);

	controller.game_loop();

	glutTimerFunc(50, time_refresh, 0);
	glutPostRedisplay();
}

void gview::GameView::reshape(int w, int h)
{
	// World ratio
	float ratio = (float)(window.right) / (float)(window.bottom);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int height = h * ratio;
	int width = (w - height) / 2;

	window_update.right = width;
	window_update.bottom = height;

	controller.window.right = width;
	controller.window.bottom = height;

	glViewport(width, 0, height, h);
	gluOrtho2D(0, window.right, window.bottom, 0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void gview::GameView::keyboard_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':
		controller.action(gctrl::GameAction::kFire);
		break;
	case 'w':
	case 'W':
		controller.action(gctrl::GameAction::kMoveUp);
		break;
	case 's':
	case 'S':
		controller.action(gctrl::GameAction::kMoveDown);
		break;
	}
	glutPostRedisplay();
}

void gview::GameView::init_window(const char* name)
{
	int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	int INITIAL_POS = 50;

	window.right = SCREEN_WIDTH / 3 * 2;
	window.bottom = SCREEN_HEIGHT / 6 * 5;

	controller.window.right = window.right;
	controller.window.bottom = window.bottom;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window.right, window.bottom);
	glutInitWindowPosition(INITIAL_POS, INITIAL_POS/2);
	glutCreateWindow((const char*)name);
}

void gview::GameView::create_scene_objects()
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

	shape = shf.get_butterfly(0.0, 0.0, 1, 1);
	shape.transform(glm::vec3(window.right - 100.0, window.bottom - 200.0, 0.0),
		glm::vec3(75), 0);
	shape.set_color(color::red, color::transparent);
	obj_layer.add_object(&shape);

}

void gview::GameView::set_first_scene()
{
	this->create_scene_objects();

	// Pass uniform variables to the shader
	// Coordinates are specified in relation to the usage domain
	// (i.e. when dealing w/ temperature, the origin could be below zero)
	Projection = ortho(0.0f, float(window.right), 0.0f, float(window.bottom));
	MatProj = glGetUniformLocation(obj_layer.get_id(), "Projection");
	MatMod = glGetUniformLocation(obj_layer.get_id(), "Model");

}

void gview::GameView::init_view()
{
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	this->init_window("my_game_app");

	controller = gctrl::GameController();
	controller.init_game(&obj_layer);

	glutDisplayFunc(this->draw_scene);
	glutTimerFunc(50, this->time_refresh, 0);
	glutReshapeFunc(this->reshape);

	// Handle mouse inputs
	//mouse.assignRefScene(&scene);
	glutKeyboardFunc(this->keyboard_handler);

	glewExperimental = GL_TRUE;
	glewInit();

	obj_layer.set_shaders((char*)"vertexShader.glsl", (char*)"fragmentShader.glsl");
	this->set_first_scene();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}
