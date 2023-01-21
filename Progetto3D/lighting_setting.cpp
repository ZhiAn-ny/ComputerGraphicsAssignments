#include "lighting_setting.h"

using namespace util::uvar;

lgh::LightingSettings::LightingSettings()
{
	this->ambient_light_.set_intensity(0.1);

	this->diffuse_light_.set_position(vec3(3));
	this->diffuse_light_.set_color(vec3(res::color::white));
	this->diffuse_light_.set_intensity(1);

}

lgh::LightingSettings::~LightingSettings()
{
}

void lgh::LightingSettings::render(Shader* sh)
{
	sh->setVec3(am_light, this->ambient_light_.get_color());
	sh->setFloat(am_light_pwr, this->ambient_light_.get_intensity());

	sh->setVec3(diff_light_pos, this->diffuse_light_.get_position());
	sh->setVec3(diff_light, this->diffuse_light_.get_color());
	sh->setFloat(diff_light_pwr, this->diffuse_light_.get_intensity());

}
