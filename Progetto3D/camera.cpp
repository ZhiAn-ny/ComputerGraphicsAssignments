#include "camera.h"

gview::gcam::Camera::Camera()
{
	this->pos_ = vec3(0.0f, 0.0f, 3.0f);
	//this->target_ = vec3(0.0f, 0.0f, 0.0f);
	this->dir_ = normalize(this->pos_ - this->target_);
	this->up_ = vec3(0.0f, 1.0f, 0.0f);
	this->front_ = vec3(0.0f, 0.0f, -1.0f);
	this->target_ = this->pos_ + this->front_;
}

gview::gcam::Camera::~Camera()
{
}

mat4 gview::gcam::Camera::get_view()
{
	this->target_ = this->pos_ + this->front_;
	return lookAt(this->pos_, this->target_, this->up_);
}

float gview::gcam::Camera::get_fov()
{
	return this->fov_;
}

vec3 gview::gcam::Camera::get_position()
{
	return this->pos_;
}

vec3 gview::gcam::Camera::get_front_direction()
{
	return this->front_;
}

void gview::gcam::Camera::move(dir::Directions dir)
{
	// TODO: check for collisions and prevent movement
	switch (dir)
	{
	case util::dir::Directions::front:
		this->pos_ += this->speed_ * this->front_;
		break;
	case util::dir::Directions::back:
		this->pos_ -= this->speed_ * this->front_;
		break;
	case util::dir::Directions::left:
		this->pos_ -= normalize(cross(this->front_, this->up_)) * this->speed_;
		break;
	case util::dir::Directions::right:
		this->pos_ += normalize(cross(this->front_, this->up_)) * this->speed_;
		break;
	default:
		break;
	}
}

void gview::gcam::Camera::activate_trackball(int x, int y)
{
	this->is_active_ = true;
	this->last_mouse_pos = vec2(x, y);
}

void gview::gcam::Camera::deactivate_trackball()
{
	this->is_active_ = false;
}

void gview::gcam::Camera::rotate(int x, int y)
{
	if (!this->is_active_) return;

	float xoffset = x - this->last_mouse_pos.x;
	float yoffset = y - this->last_mouse_pos.y;
	this->last_mouse_pos = vec2(x, y);

	xoffset = xoffset * this->sensitivity_;
	yoffset = yoffset * this->sensitivity_;

	this->yaw = this->yaw - xoffset;
	this->pitch = this->pitch + yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	vec3 front;
	front.x = cos(radians(this->yaw)) * cos(radians(this->pitch));
	front.y = sin(radians(this->pitch));
	front.z = sin(radians(this->yaw)) * cos(radians(this->pitch));

	this->front_ = normalize(front);
}

void gview::gcam::Camera::zoom_in()
{
	this->fov_ = this->fov_ + 1;
	if (this->fov_ > 90.0f)
		this->fov_ = 90.0f;
}

void gview::gcam::Camera::zoom_out()
{
	this->fov_ = this->fov_ - 1;
	if (this->fov_ < 1.0f)
		this->fov_ = 1.0f;
}
