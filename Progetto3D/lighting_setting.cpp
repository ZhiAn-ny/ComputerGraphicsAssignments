#include "lighting_setting.h"

using namespace util::uvar;

lgh::LightingSettings::LightingSettings() { }

lgh::LightingSettings::~LightingSettings() { }

void lgh::LightingSettings::set_point_light_position(vec3 pos)
{
	this->point.set_position(pos);
}

void lgh::LightingSettings::set_point_light_params(vec3 ambient, vec3 diffuse, vec3 specular)
{
	this->point.set_lights(ambient, diffuse, specular);
}

void lgh::LightingSettings::render(Shader* sh)
{
	sh->setVec3("light.pos", this->point.get_position());

	sh->setVec3("light.ambient", this->point.get_ambient());
	sh->setVec3("light.diffuse", this->point.get_diffuse());
	sh->setVec3("light.specular", this->point.get_specular());
	
}
