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

void lgh::PointLight::render(Shader* sh)
{
	sh->setVec3("light.pos", this->src_pos_);

	sh->setVec3("light.ambient", this->get_ambient());
	sh->setVec3("light.diffuse", this->get_diffuse());
	sh->setVec3("light.specular", this->get_specular());

}
