#include "camera.h"

gview::gcam::Camera::Camera()
{
	this->pos_ = vec3(0.0f, 0.0f, 3.0f);
	this->target_ = vec3(0.0f, 0.0f, 0.0f);
	this->dir_ = normalize(this->pos_ - this->target_);
	this->up_ = vec3(0.0f, 1.0f, 0.0f);
	this->front_ = vec3(0.0f, 1.0f, 0.0f);
}

gview::gcam::Camera::~Camera()
{
}

mat4 gview::gcam::Camera::get_view()
{
	return lookAt(this->pos_, this->target_, this->up_);
}

void gview::gcam::Camera::move(dir::Directions dir)
{
	vec3 dir_vec = {};
	switch (dir)
	{
	case util::dir::Directions::front:
		dir_vec = dir::front;
		break;
	case util::dir::Directions::back:
		dir_vec = dir::back;
		break;
	case util::dir::Directions::up:
		dir_vec = dir::up;
		break;
	case util::dir::Directions::down:
		dir_vec = dir::down;
		break;
	case util::dir::Directions::left:
		dir_vec = dir::left;
		break;
	case util::dir::Directions::right:
		dir_vec = dir::right;
		break;
	default:
		break;
	}

	this->pos_ += this->speed_ * dir_vec;
	this->target_ += this->speed_ * dir_vec;
}
