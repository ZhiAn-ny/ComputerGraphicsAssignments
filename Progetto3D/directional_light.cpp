#include "directional_light.h"

lgh::DirectionalLight::DirectionalLight()
{
}

lgh::DirectionalLight::~DirectionalLight()
{
}

void lgh::DirectionalLight::set_direction(vec3 dir)
{
	this->direction_ = dir;
}

void lgh::DirectionalLight::render(Shader* sh)
{
	sh->setVec3("light.dir", this->direction_);

	sh->setVec3("light.ambient", this->get_ambient());
	sh->setVec3("light.diffuse", this->get_diffuse());
	sh->setVec3("light.specular", this->get_specular());
}
