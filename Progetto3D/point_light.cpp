#include "point_light.h"

lgh::PointLight::PointLight() { }

lgh::PointLight::~PointLight() { }

lgh::PointLight::PointLight(string name)
{
	this->set_name(name);
}

vec3 lgh::PointLight::get_position()
{
	return this->src_pos_;
}

void lgh::PointLight::set_position(vec3 pos)
{
	this->src_pos_ = pos;
}

void lgh::PointLight::set_params(float linear, float quadratic)
{
	this->linear_ = linear;
	this->quadratic_ = quadratic;
}

void lgh::PointLight::render(Shader* sh)
{
	sh->setVec3("light.pos", this->src_pos_);

	sh->setVec3("light.ambient", this->get_ambient());
	sh->setVec3("light.diffuse", this->get_diffuse());
	sh->setVec3("light.specular", this->get_specular());

	sh->setFloat("light.constant", this->constant_);
	sh->setFloat("light.linear", this->linear_);
	sh->setFloat("light.quadratic", this->quadratic_);

}
