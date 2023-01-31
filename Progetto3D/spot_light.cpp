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

void lgh::Spotlight::set_cut_off(float cutOff)
{
	this->cutOff_ = cutOff;
}

void lgh::Spotlight::render(Shader* sh)
{
	sh->setVec3("light.dir", this->direction_);
	sh->setFloat("light.cutOff", cos(radians(this->cutOff_)));

	PointLight::render(sh);
}
