#ifndef GAME_LIGHT_FACTORY_H_
#define GAME_LIGHT_FACTORY_H_

#include "alight.h"
#include "point_light.h"
#include "directional_light.h"
#include "spot_light.h"

namespace lgh {

	class LightFactory {
	private:
		unsigned int n_pl = 0;
		unsigned int n_dl = 0;
		unsigned int n_sl = 0;

	public:
		LightFactory();
		~LightFactory();

		PointLight new_point_light(vec3 pos);
		PointLight new_point_light(vec3 pos, vec3 color);

		Spotlight new_spotlight(vec3 pos);
		Spotlight new_spotlight(vec3 pos, vec3 dir);

		DirectionalLight new_directional_light(vec3 dir);

	};

}

#endif // !GAME_LIGHT_FACTORY_H_
