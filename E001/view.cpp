#include "view.h"



static unsigned int MatMod, MatProj;
mat4 Projection;

gscene::Scene scene;
//Mouse mouse;


gview::GameView::GameView() { }

gview::GameView::~GameView() { }

void gview::GameView::draw_scene(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	scene.draw_scene(&MatMod, &MatProj, &Projection);

	glutSwapBuffers();
}

void gview::GameView::time_refresh(int value)
{
	float angolo = 0.0;
	float trasFactor;
	float minObjY = margin_bottom;
	float maxObjY = margin_top;
	float ray = default_figure_ray;
	std::string moving = "butterfly_0";

	//vec3 objPos = scene.getObjectPosition(moving);
	//Direction dir = scene.getObjectDirection(moving);

	//float y = (ray * 2 * (dir / abs((int)dir))) + objPos.y;

	//// Change direction
	//if (y < minObjY)
	//	scene.changeObjectDirection(moving, Direction::UP);
	//if (y > maxObjY)
	//	scene.changeObjectDirection(moving, Direction::DOWN);


	//// Create base translation vector
	//vec3 tVector = vec3((dir / 2), (dir % 2), 0.0);

	//// trasFactor = (dir / abs((int) dir));
	//// 
	//// tVector.x *= trasFactor;
	//// tVector.y *= trasFactor;

	//vec3 sv = vec3(1.0, 1.0, 1.0); // Leave z axis untouched

	//scene.transformObject(moving, tVector, sv, angolo);

	glutTimerFunc(50, time_refresh, 0);
	glutPostRedisplay();
}

void gview::GameView::init_window(const char* name)
{
	int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	this->window_.right = SCREEN_WIDTH / 3;
	this->window_.bottom = SCREEN_HEIGHT / 2;

	gview::margin_bottom = this->window_.bottom / 4;
	gview::margin_top = this->window_.bottom - gview::margin_bottom;
	gview::default_figure_ray = this->window_.bottom / 10;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(this->window_.right, this->window_.bottom);
	glutInitWindowPosition(100, 100);
	glutCreateWindow((const char*) name);
}

void gview::GameView::create_scene_objects()
{
	ShapeFactory shf;
	gso::SceneObject shape;
	std::string name;

	// Add scene objects to render on start
	shape = shf.getButterfly(0.0, 0.0, 1, 1);
	// Set initial direction
	//shape.dir = Direction::UP;
	scene.add_object(&shape);
	name = shape.get_name();
	// Set initial position and scale
	scene.transformObject(name, vec3(100.0, this->window_.bottom - 200.0, 0.0),
		vec3(this->window_.bottom / 10), 0);

	{
		shape = shf.getButterfly(0.0, 0.0, 1, 1);
		//shape.dir = Direction::UP;
		scene.add_object(&shape);
		name = shape.get_name();
		// Set initial position and scale
		scene.transformObject(name, vec3(100.0, this->window_.bottom / 4, 0.0),
			vec3(this->window_.bottom / 10), 0);

		shape = shf.getButterfly(0.0, 0.0, 1, 1);
		//shape.dir = Direction::UP;
		scene.add_object(&shape);
		name = shape.get_name();
		// Set initial position and scale
		scene.transformObject(name, vec3(100.0, this->window_.bottom / 4 * 3, 0.0),
			vec3(this->window_.bottom / 10), 0);
	}
}

void gview::GameView::set_first_scene()
{
	this->create_scene_objects();

	// Pass uniform variables to the shader
	// Coordinates are specified in relation to the usage domain
	// (i.e. when dealing w/ temperature, the origin could be below zero)
	Projection = ortho(0.0f, float(this->window_.right), 0.0f, float(this->window_.bottom));
	MatProj = glGetUniformLocation(scene.get_id(), "Projection");
	MatMod = glGetUniformLocation(scene.get_id(), "Model");

}

void gview::GameView::init_view()
{
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	this->init_window("my_game_app");

	glutDisplayFunc(this->draw_scene);

	// Handle mouse inputs
	//mouse.assignRefScene(&scene);

	glutTimerFunc(50, this->time_refresh, 0);

	glewExperimental = GL_TRUE;
	glewInit();

	scene.set_shaders((char*)"vertexShader.glsl", (char*)"fragmentShader.glsl");
	this->set_first_scene();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}
