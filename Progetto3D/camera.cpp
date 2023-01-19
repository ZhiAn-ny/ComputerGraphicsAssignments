#include "camera.h"

gview::gcam::Camera::Camera()
{
	this->pos_ = vec3(0.0f, 0.0f, 3.0f);
	this->target_ = vec3(0.0f, 0.0f, 0.0f);
	this->dir_ = normalize(this->pos_ - this->target_);
	this->up_ = vec3(0.0f, 1.0f, 0.0f);
}

gview::gcam::Camera::~Camera()
{
}

mat4 gview::gcam::Camera::get_view()
{
	return lookAt(this->pos_, this->target_, this->up_);
}
