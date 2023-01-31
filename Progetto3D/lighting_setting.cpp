#include "lighting_setting.h"

using namespace util::uvar;

lgh::LightingSettings::LightingSettings() { }

lgh::LightingSettings::~LightingSettings() { }

void lgh::LightingSettings::add_point_light(PointLight light)
{
	this->point.push_back(light);
}

void lgh::LightingSettings::add_spotlight(Spotlight light)
{
	this->spot.push_back(light);
}

void lgh::LightingSettings::add_directional_light(DirectionalLight light)
{
	this->direct.push_back(light);
}

void lgh::LightingSettings::render(Shader* sh)
{
	string var_name;

	sh->setInt("n_dirLights", this->direct.size());
	for (int i = 0; i < this->direct.size(); i++)
	{
		var_name = "dirLights[" + std::to_string(i) + "]";
		this->direct[i].render(sh, var_name);
	}

	sh->setInt("n_pointLights", this->point.size());
	for (int i = 0; i < this->point.size(); i++)
	{
		var_name = "pointLights[" + std::to_string(i) + "]";
		this->point[i].render(sh, var_name);
	}

	sh->setInt("n_spotlights", this->spot.size());
	for (int i = 0; i < this->spot.size(); i++)
	{
		var_name = "spotlights[" + std::to_string(i) + "]";
		this->spot[i].render(sh, var_name);
	}

}
