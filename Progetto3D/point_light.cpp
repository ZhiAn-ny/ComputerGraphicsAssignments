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

void lgh::PointLight::render(Shader* sh, string uvar)
{
	sh->setVec3(uvar + ".pos", this->src_pos_);

	sh->setVec3(uvar + ".ambient", this->get_ambient());
	sh->setVec3(uvar + ".diffuse", this->get_diffuse());
	sh->setVec3(uvar + ".specular", this->get_specular());

	sh->setFloat(uvar + ".constant", this->constant_);
	sh->setFloat(uvar + ".linear", this->linear_);
	sh->setFloat(uvar + ".quadratic", this->quadratic_);

}
