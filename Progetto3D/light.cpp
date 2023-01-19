#include "light.h"

lgh::Light::Light() { }

lgh::Light::~Light() { }

vec3 lgh::Light::get_color()
{
    return this->color_;
}

void lgh::Light::set_color(vec3 color)
{
    this->color_ = color;
}

float lgh::Light::get_intensity()
{
    return this->pwr_;
}

void lgh::Light::set_intensity(float i)
{
    this->pwr_ = i;
}
