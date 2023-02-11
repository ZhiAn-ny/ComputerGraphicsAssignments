#include "light_factory.h"

using namespace lgh;

lgh::LightFactory::LightFactory() { }

lgh::LightFactory::~LightFactory() { }

PointLight LightFactory::new_point_light(vec3 pos)
{
    PointLight light = PointLight("pointlight_" + this->n_pl);

    light.set_position(pos);

    light.set_lights(vec3(0.2), vec3(0.5), vec3(1));
    light.set_params(0.09, 0.032);

    this->n_pl++;
    return light;
}

PointLight lgh::LightFactory::new_point_light(vec3 pos, vec3 color)
{
    PointLight pl = this->new_point_light(pos);
    pl.set_color(color);
    return pl;
}

Spotlight LightFactory::new_spotlight(vec3 pos)
{
    Spotlight light = Spotlight("spotlight_" + this->n_sl);

    light.set_position(pos);
    light.set_direction(vec3(0, -1, 0));

    light.set_inner_cutOff(12.5);
    light.set_outer_cutOff(17.5);

    light.set_lights(vec3(0.2), vec3(0.5), vec3(1));
    light.set_params(0.09, 0.032);

    this->n_sl++;
    return light;
}

Spotlight LightFactory::new_spotlight(vec3 pos, vec3 dir)
{
    Spotlight light = this->new_spotlight(pos);
    light.set_direction(dir);

    return light;
}

DirectionalLight LightFactory::new_directional_light(vec3 dir)
{
    DirectionalLight light = DirectionalLight("directional_" + this->n_dl);

    light.set_direction(dir);
    light.set_lights(vec3(0.2), vec3(0.5), vec3(1));

    this->n_dl++;
    return light;
}
