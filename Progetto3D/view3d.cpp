#include "view3d.h"

// GLOBAL VARIABLES

RECT window;
Scene scene;
Shader main_shader;
Shader cm_shader;
Camera cam;
gview::sky::Cubemap skybox;

lgh::LightingSettings light_setting;
gctrl::GameController controller;

mat4 Projection;

/******************************************************************************/
// STATIC FUNCTIONS

void gview::GameView3D::draw_scene(void)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Projection = perspective(glm::radians(cam.get_fov()), 800.0f / 600.0f, near_plane, far_plane);

	// Render the cubemap
	cm_shader.use();
	cm_shader.setMatrix4f("Projection", Projection);
	cm_shader.setMatrix4f("View", cam.get_view());
	
	skybox.render(&cm_shader, &cam);

	// Render everything else
	main_shader.use();
	main_shader.setMatrix4f("Projection", Projection);
	main_shader.setMatrix4f("View", cam.get_view());

	main_shader.setVec3("camPos", cam.get_position());

	light_setting.render(&main_shader);

	scene.render(&main_shader);

	glutSwapBuffers();
}

void gview::GameView3D::time_refresh(int a)
{
	//scene.transform_object("cube_0", vec3(0), vec3(1), vec3(1, 1, 0), 0.1);
	//scene.get_object("cube_0")->turn(Directions::up);

	scene.for_each(
		[](mesh::IMesh* mesh) { return mesh->get_name().substr(0, 5)._Equal("whale"); },
		[](mesh::IMesh* mesh) {
			mesh->move(Directions::front);
			mesh->turn(EulerAngle::yaw_left, 0.1);
		}
	);

	scene.for_each(
		[](mesh::IMesh* mesh) { return mesh->get_name().substr(0, 5)._Equal("manta"); },
		[](mesh::IMesh* mesh) {
			mesh->move(Directions::front);
			mesh->turn(EulerAngle::yaw_right);
		}
	);

	scene.get_object("dolphin_0")->turn(EulerAngle::yaw_right);
	scene.get_object("dolphin_0")->move(Directions::front);
	scene.get_object("dolphin_1")->turn(EulerAngle::yaw_left);
	scene.get_object("dolphin_1")->move(Directions::front);

	scene.for_each(
		[](mesh::IMesh* mesh) { return mesh->get_name().substr(0, 5)._Equal("fish_"); },
		[](mesh::IMesh* mesh) {
			mesh->move(Directions::front);
			if (mesh->get_pos().x < -10 || mesh->get_pos().x > 10 ||
				mesh->get_pos().z < -10 || mesh->get_pos().z > 10)
			{
				mesh->move(Directions::back, 0.5);
				mesh->turn(EulerAngle::yaw_right, 90);
			}
		}
	);

	scene.for_each(
		[](mesh::IMesh* mesh) { return mesh->get_name().substr(0, 5)._Equal("jelly"); },
		[](mesh::IMesh* mesh) {
			mesh->move(Directions::front);
			mesh->turn(EulerAngle::yaw_left);
			if (mesh->get_pos().y > 30)
				mesh->transform(vec3(0, -60, 0), vec3(1), vec3(1, 0, 0), 0);
		}
	);

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
	case 'E': case 'e':
		cam.move(dir::Directions::up);
		break;
	case 'Q': case 'q':
		cam.move(dir::Directions::down);
		break;
	case 'O': case 'o':
		cam.to_origin();
		break;
	case 'j':
		cam.set_position(scene.get_object("jellyfish_0")->get_pos());
		break;
	case 'b':
		cam.set_position(scene.get_object("whale_0")->get_pos());
		break;
	}
}

void gview::GameView3D::mouse_click(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			cam.activate_trackball(x, y);
		if (state == GLUT_UP)
			cam.deactivate_trackball();
		break;
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			//std::cout << "Clicked point: (" << x << ", " << y << ")" << std::endl;
			controller.select_object(x, y);
		}
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

void gview::GameView3D::menu_event_handler(int event)
{
	if (event == gctrl::MenuActions::deselect) 
	{
		controller.deselect_all();
		return;
	}

	gctrl::MenuActions action = static_cast<gctrl::MenuActions>(event);
	if (event > 0) 
		controller.change_selected_material(action);
	else 
		controller.change_selected_shading(action);
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
	// Set scene's lights
	lgh::LightFactory lf;
	lgh::PointLight pl;

	light_setting.add_directional_light(lf.new_directional_light(vec3(0,0,-1)));
	
	pl = lf.new_point_light(vec3(5), color::orange);
	light_setting.add_point_light(pl);
	pl = lf.new_point_light(vec3(-3), color::blue);
	light_setting.add_point_light(pl);
	pl = lf.new_point_light(vec3(0,-5,0), color::cyan);
	light_setting.add_point_light(pl);

	////////////////////////////////////////////////////////////////////////////

	// Set scene's objects
	mesh::MeshFactory mf;
	mesh::Mesh mesh;
	mesh::Model model;

	// Add torus
	for (float x = -5.7; x < 6; x += 5.7)
	{
		mesh = mf.create_torus();
		mesh.add_texture("rainbow", "res/textures/rainbow.png", 1);
		mesh.set_diffuse_map("rainbow");
		mesh.set_material(tutorial, true);
		mesh.transform(vec3(x, 0, 0), vec3(1), vec3(1, 0, 0), 90);
		scene.add_object(mesh);
	}

	model = mf.create_dolphin();
	model.transform(vec3(-5.7, 0, 0), vec3(0.5), vec3(1, 0, 0), 0);
	scene.add_object(model);
	model = mf.create_dolphin();
	model.transform(vec3(0), vec3(0.5), vec3(0, 1, 0), 180);
	scene.add_object(model);

	model = mf.create_manta();
	model.transform(vec3(-8,-5,-3), vec3(0.4), vec3(1, 0, 0), 0);
	model.turn(EulerAngle::pitch_up, 30);
	model.turn(EulerAngle::roll_left, 10);
	scene.add_object(model);
	model = mf.create_manta();
	model.transform(vec3(-10,-6,-1), vec3(0.4), vec3(1, 0, 0), 0);
	model.turn(EulerAngle::pitch_up, 30);
	model.turn(EulerAngle::roll_left, 10);
	scene.add_object(model);
	model = mf.create_manta();
	model.transform(vec3(-15, -9, 0), vec3(0.4), vec3(1, 0, 0), 0);
	model.turn(EulerAngle::pitch_up, 30);
	model.turn(EulerAngle::roll_left, 10);
	scene.add_object(model);

	// Create whales
	model = mf.create_whale();
	model.transform(vec3(0, 0, -132), vec3(1.3), vec3(0, 1, 0), -90);
	model.turn(EulerAngle::pitch_down, 30);
	scene.add_object(model);
	model = mf.create_whale();
	model.transform(vec3(0, -3, -130), vec3(0.9), vec3(0, 1, 0), -90);
	model.turn(EulerAngle::pitch_down, 30);
	scene.add_object(model);

	// Add jellyfish
	for (unsigned int i = 0; i < 5; i++)
	{
		model = mf.create_jellyfish();
		model.transform(vec3(
			(rand() % 4 - 5) / 2.0,
			(rand() % 4 - 15) / 2.0,
			(rand() % 4 - 5) / 2.0
		), vec3(1), vec3(0, 0, 1), 0);
		model.set_speed(0.001);
		scene.add_object(model);
	}

	//gobj::mesh::Mesh mesh = mf.create_cube();
	//mesh.add_texture("opal", "res/textures/opal.jpg", 1);
	//mesh.set_diffuse_map("opal");
	//mesh.set_material(tutorial, true);
	//scene.add_object(mesh);

	// Add fishes
	for (unsigned int i = 0; i < 30; i++)
	{
		model = mf.create_fish();
		model.transform(vec3(
			(rand() % 18 - 9) / 3.0,
			(rand() % 12 - 6) / 3.0,
			(rand() % 18 - 9) / 3.0
		), vec3(0.05), vec3(0, 0, 1), 0);

		model.turn(EulerAngle::yaw_left, 90);
		switch (rand() % 3)
		{
		case 0:
			model.set_material(brass);
			break;
		case 1:
			model.set_material(gold);
			break;
		case 2:
			model.set_material(no_material, true);
			break;
		}
		model.set_speed(0.2);
		scene.add_object(model);
	}

}

void gview::GameView3D::setup_menu()
{
	int material_options = glutCreateMenu(this->menu_event_handler);
	glutAddMenuEntry("Use tutorial material", gctrl::MenuActions::mat_tutorial);
	glutAddMenuEntry("Use jade material", gctrl::MenuActions::mat_jade);
	glutAddMenuEntry("Use gold material", gctrl::MenuActions::mat_gold);
	glutAddMenuEntry("Use brass material", gctrl::MenuActions::mat_brass);
	glutAddMenuEntry("Use .mtl file", gctrl::MenuActions::mat_mtl);
	glutAddMenuEntry("Remove material", gctrl::MenuActions::no_mat);

	int shading_options = glutCreateMenu(this->menu_event_handler);
	glutAddMenuEntry("Render with phong (phong)", gctrl::MenuActions::sh_phong_phong);
	glutAddMenuEntry("Render with blinn-phong (phong)", gctrl::MenuActions::sh_blinn_phong_phong);
	glutAddMenuEntry("Render with phong (interpolative)", gctrl::MenuActions::sh_phong_interp);
	glutAddMenuEntry("Render with blinn-phong (interpolative)", gctrl::MenuActions::sh_blinn_phong_interp);
	glutAddMenuEntry("Render with cartoon", gctrl::MenuActions::sh_cartoon);

	glutCreateMenu(this->menu_event_handler);

	glutAddSubMenu("Change Material", material_options);
	glutAddSubMenu("Change Shading", shading_options);
	glutAddMenuEntry("Deselect All", gctrl::MenuActions::deselect);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void gview::GameView3D::init()
{
	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	this->create_window("Space Ocean");

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

	controller.init(&scene, &window, &Projection, &cam);
	main_shader = Shader("vertexShader.glsl", "fragmentShader.glsl");
	cm_shader = Shader("cubemap_vs.glsl", "cubemap_fs.glsl");
	
	skybox.init();
	skybox.set_theme(res::sky::SkyBoxThemes::space);
	this->set_scene();

	this->setup_menu();

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
