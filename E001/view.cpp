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
	std::string moving = "butterfly_0";

	std::string bottom = "butterfly_1";
	std::string top = "butterfly_2";

	gso::SceneObject* shape = obj_layer.get_object(moving);
	gso::SceneObject* bshape = obj_layer.get_object(bottom);
	gso::SceneObject* tshape = obj_layer.get_object(top);

	gso::Direction dir = shape->get_direction();
	glm::vec3 pos = shape->get_position();

	// Change direction
	if (shape->is_colliding(*bshape))
		shape->change_direction(gso::Direction::kUp);
	if (shape->is_colliding(*tshape))
		shape->change_direction(gso::Direction::kDown);

	shape->move(0.1);

	glutTimerFunc(50, time_refresh, 0);
	glutPostRedisplay();
}

void gview::GameView::reshape(int w, int h)
{
	// World ratio
	float ratio = (float)(window.right) / (float)(window.bottom);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int width = h * ratio;
	int left = (w - width) / 2;
	glViewport(left, 0, width, h);
	gluOrtho2D(0, window.right, window.bottom, 0);
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void gview::GameView::keyboard_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case ' ':

		break;
	case 'w':
	case 'W':

		break;
	case 's':
	case 'S':

		break;
	}
	glutPostRedisplay();
}

void gview::GameView::init_window(const char* name)
{
	int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	window.right = SCREEN_WIDTH / 3;
	window.bottom = SCREEN_HEIGHT / 2;

	gview::margin_bottom = window.bottom / 4;
	gview::margin_top = window.bottom - gview::margin_bottom;
	gview::default_figure_ray = window.bottom / 10;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window.right, window.bottom);
	glutInitWindowPosition(100, 100);
	glutCreateWindow((const char*)name);
}

void gview::GameView::create_scene_objects()
{
	gsf::ShapeFactory shf;
	gso::SceneObject shape;
	std::string name;

	// Add scene objects to render on start
	shape = shf.getButterfly(0.0, 0.0, 1, 1);
	// Set initial direction
	//shape.dir = Direction::UP;
	shape.transform(glm::vec3(100.0, window.bottom - 200.0, 0.0),
		glm::vec3(window.bottom / 10), 0);
	obj_layer.add_object(&shape);
	name = shape.get_name();
	// Set initial position and scale

	{
		shape = shf.getButterfly(0.0, 0.0, 1, 1);
		//shape.dir = Direction::UP;
		shape.transform(glm::vec3(100.0, window.bottom / 4, 0.0),
			glm::vec3(window.bottom / 10), 0);
		obj_layer.add_object(&shape);
		name = shape.get_name();
		// Set initial position and scale

		shape = shf.getButterfly(0.0, 0.0, 1, 1);
		//shape.dir = Direction::UP;
		shape.transform(glm::vec3(100.0, window.bottom / 4 * 3, 0.0),
			glm::vec3(window.bottom / 10), 0);
		obj_layer.add_object(&shape);
		name = shape.get_name();
		// Set initial position and scale
	}

	//shape = shf.get_curve();
	//shape.transform(glm::vec3(250.0, window.bottom / 4 * 3, 0.0),
	//	glm::vec3(window.bottom / 10), 0);
	//obj_layer.add_object(&shape);
	//name = shape.get_name();

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

	controller = gctrl::GameController();
	controller.init_game(&obj_layer);

	this->init_window("my_game_app");

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

gscene::Scene* gview::GameView::get_obj_layer_scene()
{
	return &obj_layer;
}
