#include "alight.h"

string lgh::ALight::get_name() { return this->name_; }
void lgh::ALight::set_name(string name) { this->name_ = name; }

void lgh::ALight::turn_on() { this->is_on = true; }
void lgh::ALight::turn_off() { this->is_on = false; }

vec3 lgh::ALight::get_ambient() { return this->ambient_; }
vec3 lgh::ALight::get_specular() { return this->specular_; }
vec3 lgh::ALight::get_diffuse() { return this->diffuse_; }

void lgh::ALight::set_ambient(vec3 color) { this->ambient_ = color; }
void lgh::ALight::set_diffuse(vec3 color) { this->diffuse_ = color; }
void lgh::ALight::set_specular(vec3 color) { this->specular_ = color; }

void lgh::ALight::set_lights(vec3 ambient, vec3 diffuse, vec3 specular)
{
	this->set_ambient(ambient);
	this->set_diffuse(diffuse);
	this->set_specular(specular);
}

void lgh::ALight::set_color(vec3 color)
{
	this->ambient_ *= color;
	this->diffuse_ *= color;
	this->specular_ *= color;
}
