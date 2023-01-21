#include "lighting_setting.h"

using namespace util::uvar;

lgh::LightingSettings::LightingSettings() { }

lgh::LightingSettings::~LightingSettings() { }

void lgh::LightingSettings::set_position(vec3 pos)
{
	this->src_pos = pos;
}

void lgh::LightingSettings::set_lights(vec3 ambient, vec3 diffuse, vec3 specular)
{
	this->ambient_ = ambient;
	this->diffuse_ = diffuse;
	this->specular_ = specular;
}

void lgh::LightingSettings::render(Shader* sh)
{
	sh->setVec3("light.pos", this->src_pos);

	sh->setVec3("light.ambient", this->ambient_);
	sh->setVec3("light.diffuse", this->diffuse_);
	sh->setVec3("light.specular", this->specular_);
	
}
