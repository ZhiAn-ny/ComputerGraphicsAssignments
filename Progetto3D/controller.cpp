#include "controller.h"

gctrl::GameController::GameController() { }

gctrl::GameController::~GameController() { }

void gctrl::GameController::init(Scene* scene, RECT* window, mat4* proj, Camera* cam)
{
	this->scene_ = scene;
	this->win_ = window;
	this->Projection_ = proj;
	this->cam_ = cam;
}

vec3 gctrl::GameController::get_ray(int x, int y)
{
	// Get y from bottom edge (not from window's top edge)
	y = this->win_->bottom - y;

	// Map to normalized coordinates
	float nx = ((2.0 * x) / this->win_->right) - 1.0;
	float ny = ((2.0 * y) / this->win_->bottom) - 1.0;

	vec4 clip_space_ray = vec4(nx, ny, -1.0, 1.0);
	vec4 eye_ray = inverse(*Projection_) * clip_space_ray;
	
	// Get eye ray direction
	eye_ray = vec4(eye_ray.x, eye_ray.y, -1.0, 0.0);

	// Map to world's coordinates
	vec3 world_ray = vec3(inverse(this->cam_->get_view()) * eye_ray);
	world_ray = normalize(world_ray);

	return world_ray;
}

void gctrl::GameController::select_object(int x, int y)
{
	vec3 mouse_ray = this->get_ray(x, y);
	std:cout << "(" << mouse_ray.x << "," 
			 << mouse_ray.y << "," 
			 << mouse_ray.z << ")" << std::endl;
	vec3 origin = this->cam_->get_position();
	//this->scene_->select_nearest(origin, mouse_ray);
}
