#include "directional_light.h"

lgh::DirectionalLight::DirectionalLight()
{
}

lgh::DirectionalLight::DirectionalLight(string name)
{
	this->set_name(name);
}

lgh::DirectionalLight::~DirectionalLight()
{
}

void lgh::DirectionalLight::set_direction(vec3 dir)
{
	this->direction_ = dir;
}

void lgh::DirectionalLight::render(Shader* sh, string uvar)
{
	sh->setVec3(uvar + ".dir", this->direction_);

	sh->setVec3(uvar + ".ambient", this->get_ambient());
	sh->setVec3(uvar + ".diffuse", this->get_diffuse());
	sh->setVec3(uvar + ".specular", this->get_specular());
}
