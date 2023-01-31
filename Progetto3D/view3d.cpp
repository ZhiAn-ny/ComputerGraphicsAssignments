#include "view3d.h"

// GLOBAL VARIABLES

RECT window;
Scene scene;
Shader main_shader;
Camera cam;
lgh::LightingSettings light_setting;

mat4 Projection;

/******************************************************************************/
// STATIC FUNCTIONS

void gview::GameView3D::draw_scene(void)
{
	Projection = perspective(glm::radians(cam.get_fov()), 800.0f / 600.0f, 0.1f, 100.0f);

	main_shader.use();
	main_shader.setMatrix4f("Projection", Projection);
	main_shader.setMatrix4f("View", cam.get_view());

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	main_shader.setVec3(util::uvar::cam_pos, cam.get_position());

	light_setting.render(&main_shader);

	scene.render(&main_shader);

	glutSwapBuffers();
}

void gview::GameView3D::time_refresh(int a)
{
	//scene.transform_object("cube_0", vec3(0), vec3(1), vec3(5, 1, 0), 1);
	glutTimerFunc(10, GameView3D::time_refresh, 0);
	glutPostRedisplay();
}

void gview::GameView3D::resize(int w, int h)
{
}

void gview::GameView3D::key_pressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W': case 'w':
		cam.move(dir::Directions::front);
		break;
	case 'A': case 'a':
		cam.move(dir::Directions::left);
		break;
	case 'S': case 's':
		cam.move(dir::Directions::back);
		break;
	case 'D': case 'd':
		cam.move(dir::Directions::right);
		break;
	}
}

void gview::GameView3D::mouse_click(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			cam.activate_trackball(x, y);
		if (state == GLUT_UP)
			cam.deactivate_trackball();
		break;
	case util::mouse_wheel_up:
		cam.zoom_in();
		break;
	case util::mouse_wheel_down:
		cam.zoom_out();
		break;
	default:
		break;
	}
}

void gview::GameView3D::mouse_motion(int x, int y)
{
	cam.rotate(x, y);
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
	//vec3 light_pos = vec3(1.2, 1, 2);
	light_setting.set_spot_light_position(cam.get_position());
	light_setting.set_spot_light_direction(cam.get_front_direction());
	light_setting.set_spot_light_inner_cut_off(12.5);
	light_setting.set_spot_light_outer_cut_off(17.5);
	light_setting.set_spot_light_params(vec3(0.2), vec3(0.5), vec3(1));
	light_setting.set_spot_light_params(0.09, 0.032); // dist = 50

	//light_setting.set_direct_light_direction(vec3(-0.2, -1, -0.3));
	//light_setting.set_direct_light_params(vec3(0.2), vec3(0.5), vec3(1));

	mesh::MeshFactory mf;

	mesh::PolygonalMesh mesh = mf.create_cube();
	mesh.add_texture("box", "res/textures/container2.jpg", 1);
	mesh.add_texture("metal", "res/textures/container2_specular.png", 1);
	mesh.set_diffuse_map("box");
	mesh.set_specular_map("metal");
	mesh.transform(vec3(0), vec3(1), vec3(1, 0, 0), 0);
	mesh.set_material({vec3(1),vec3(1),vec3(0.5),64});
	scene.add_object(mesh);

	for (unsigned int i = 0; i < 10; i++)
	{
		mesh = mf.create_cube();
		mesh.add_texture("box", "res/textures/container2.jpg", 1);
		mesh.add_texture("metal", "res/textures/container2_specular.png", 1);
		mesh.set_diffuse_map("box");
		mesh.set_specular_map("metal");
		mesh.transform(
			vec3(rand() % 6 - 3, rand() % 6 - 3, rand() % 6 - 3),
			vec3(1),
			vec3(rand() % 20 - 10), rand()
		);
		mesh.set_material({ vec3(1),vec3(1),vec3(0.5),64 });
		scene.add_object(mesh);
	}

	//mesh = mf.create_cube();
	//mesh.transform(light_pos, vec3(0.3), vec3(1, 0, 0), 0);
	//mesh.set_color(color::white);
	//scene.add_object(mesh);

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

	glutKeyboardFunc(this->key_pressed);
	glutMouseFunc(this->mouse_click);
	glutMotionFunc(this->mouse_motion);

	// Glew is initialized after having defined glut's recurrent functions
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("glewInit failed");
	GLenum error = glGetError();

	main_shader = Shader("vertexShader.glsl", "fragmentShader.glsl");

	this->set_scene();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void gview::GameView3D::start()
{
	glutMainLoop();
}
