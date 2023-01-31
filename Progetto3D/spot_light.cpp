#include "spot_light.h"

lgh::Spotlight::Spotlight()
{
}

lgh::Spotlight::Spotlight(string name)
{
	this->set_name(name);
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

void lgh::Spotlight::render(Shader* sh, string uvar)
{
	sh->setVec3(uvar + ".dir", this->direction_);
	sh->setFloat(uvar + ".innerCutOff", cos(radians(this->inner_cutOff_)));
	sh->setFloat(uvar + ".outerCutOff", cos(radians(this->outer_cutOff_)));

	PointLight::render(sh, uvar);
}
