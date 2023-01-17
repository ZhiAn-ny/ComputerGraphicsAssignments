#include "view3d.h"

// GLOBAL VARIABLES

RECT window;
Scene scene;
Shader main_shader;

mat4 Model, View, Projection;

/******************************************************************************/
// STATIC FUNCTIONS

void gview::GameView3D::draw_scene(void)
{
	main_shader.use();
	main_shader.setMatrix4f("Projection", Projection);
	main_shader.setMatrix4f("View", View);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//main_shader.use();

	scene.render(&main_shader);

	glutSwapBuffers();
}

void gview::GameView3D::time_refresh(int a)
{
	glutTimerFunc(10, GameView3D::time_refresh, 0);
	glutPostRedisplay();
}

void gview::GameView3D::resize(int w, int h)
{
}

/******************************************************************************/

gview::GameView3D::GameView3D() { }

gview::GameView3D::~GameView3D() { }

void gview::GameView3D::create_window(const char* title)
{
	int SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	int INITIAL_POS = 50;

	window.right = SCREEN_WIDTH / 3 * 2;
	window.bottom = SCREEN_HEIGHT / 6 * 5;

	//window_update = window;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window.right, window.bottom);
	glutInitWindowPosition(INITIAL_POS, INITIAL_POS / 2);
	glutCreateWindow(title);
}

void gview::GameView3D::set_scene()
{
	mesh::PolygonalMesh mesh;

	mesh.add_vertex(mesh::Vertex(vec3(0.5, 0.5, 0.0), color::red, vec2(1, 1)));
	mesh.add_vertex(mesh::Vertex(vec3(0.5, -0.5, 0.0), color::green, vec2(1, 0)));
	mesh.add_vertex(mesh::Vertex(vec3(-0.5, -0.5, 0.0), color::blue, vec2(0, 0)));
	mesh.add_vertex(mesh::Vertex(vec3(-0.5, 0.5, 0.0), color::yellow, vec2(0, 1)));

	mesh.set_indices({0, 1, 3, 1, 2, 3});
	mesh.add_texture("box", "res/textures/test01.jpg", 1);
	mesh.set_texture("box");

	mesh.transform(vec3(0), vec3(1), vec3(1, 0, 0), -15);

	scene.add_object(mesh);
}

void gview::GameView3D::set_camera()
{
	// TODO: where to initialize these
	Projection = mat4(1);
	View = mat4(1);
	View = translate(View, glm::vec3(0.0f, 0.0f, -3.0f));
	Projection = perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void gview::GameView3D::init()
{
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	this->create_window("Is this working?");

	glutDisplayFunc(this->draw_scene);
	glutTimerFunc(10, this->time_refresh, 0);
	glutReshapeFunc(this->resize);

	// Glew is initialized after having defined glut's recurrent functions
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("glewInit failed");
	GLenum error = glGetError();

	main_shader = Shader("vertexShader.glsl", "fragmentShader.glsl");

	//cam.init(vec4(0, 0.5, 70, 0), window);
	this->set_camera();

	this->set_scene();

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	//glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void gview::GameView3D::start()
{
	glutMainLoop();
}
