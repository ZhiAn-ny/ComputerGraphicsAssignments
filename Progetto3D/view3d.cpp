#include "view3d.h"

// GLOBAL VARIABLES

RECT window;
Scene scene;
Shader main_shader;

/******************************************************************************/
// STATIC FUNCTIONS

void gview::GameView3D::draw_scene(void)
{
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
	mesh.verts = {
		mesh::Vertex(vec3(0.5, 0.5, 0.0), color::red, vec2(1, 1)),
		mesh::Vertex(vec3(0.5, -0.5, 0.0), color::green, vec2(1, 0)),
		mesh::Vertex(vec3(-0.5, -0.5, 0.0), color::blue, vec2(0, 0)),
		mesh::Vertex(vec3(-0.5, 0.5, 0.0), color::yellow, vec2(0, 1))
	};
	mesh.set_indices({0, 1, 3, 1, 2, 3});
	mesh.load_texture("res/textures/test01.jpg", 1);

	scene.add_object(mesh);
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
