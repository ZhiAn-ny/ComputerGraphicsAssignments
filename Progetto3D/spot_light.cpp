#include "spot_light.h"

lgh::Spotlight::Spotlight()
{
}

lgh::Spotlight::~Spotlight()
{
}

void lgh::Spotlight::set_direction(vec3 dir)
{
	this->direction_ = dir;
}

void lgh::Spotlight::set_inner_cutOff(float cutOff)
{
	this->inner_cutOff_ = cutOff;
}

void lgh::Spotlight::set_outer_cutOff(float cutOff)
{
	this->outer_cutOff_ = cutOff;
}

void lgh::Spotlight::render(Shader* sh)
{
	sh->setVec3("light.dir", this->direction_);
	sh->setFloat("light.innerCutOff", cos(radians(this->inner_cutOff_)));
	sh->setFloat("light.outerCutOff", cos(radians(this->outer_cutOff_)));

	PointLight::render(sh);
}
