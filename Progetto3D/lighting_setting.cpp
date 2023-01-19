#include "lighting_setting.h"

using namespace util::uvar;

lgh::LightingSettings::LightingSettings()
{
	this->ambient_light_.set_intensity(0.1);
}

lgh::LightingSettings::~LightingSettings()
{
}

void lgh::LightingSettings::render(Shader* sh)
{
	sh->setVec3(ambient_light, this->ambient_light_.get_color());
	sh->setFloat(ambient_light_pwr, this->ambient_light_.get_intensity());

}
