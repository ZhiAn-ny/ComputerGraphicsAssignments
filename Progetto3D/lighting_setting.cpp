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

void lgh::LightingSettings::set_point_light_params(float linear, float quadratic)
{
	this->point.set_params(linear, quadratic);
}

void lgh::LightingSettings::set_direct_light_direction(vec3 pos)
{
	this->direct.set_direction(pos);
}

void lgh::LightingSettings::set_direct_light_params(vec3 ambient, vec3 diffuse, vec3 specular)
{
	this->direct.set_lights(ambient, diffuse, specular);
}

void lgh::LightingSettings::set_spot_light_position(vec3 pos)
{
	this->spot.set_position(pos);
}

void lgh::LightingSettings::set_spot_light_direction(vec3 dir)
{
	this->spot.set_direction(dir);
}

void lgh::LightingSettings::set_spot_light_params(vec3 ambient, vec3 diffuse, vec3 specular)
{
	this->spot.set_lights(ambient, diffuse, specular);
}

void lgh::LightingSettings::set_spot_light_params(float linear, float quadratic)
{
	this->spot.set_params(linear, quadratic);
}

void lgh::LightingSettings::set_spot_light_inner_cut_off(float cutOff)
{
	this->spot.set_inner_cutOff(cutOff);
}

void lgh::LightingSettings::set_spot_light_outer_cut_off(float cutOff)
{
	this->spot.set_outer_cutOff(cutOff);
}

void lgh::LightingSettings::render(Shader* sh)
{
	//this->point.render(sh);
	//this->direct.render(sh);
	this->spot.render(sh);
}
