#ifndef GAME_LIGHT_SETTINGS_H_
#define GAME_LIGHT_SETTINGS_H_

#include "res.h"
#include "utils.h"
#include "point_light.h"
#include "directional_light.h"
#include "spot_light.h"

namespace lgh {

	class LightingSettings {
	private:
		PointLight point = {};
		DirectionalLight direct = {};
		Spotlight spot = {};

	public:
		LightingSettings();
		~LightingSettings();

		void set_point_light_position(vec3 pos);
		void set_point_light_params(vec3 ambient, vec3 diffuse, vec3 specular);
		void set_point_light_params(float linear, float quadratic);

		void set_direct_light_direction(vec3 dir);
		void set_direct_light_params(vec3 ambient, vec3 diffuse, vec3 specular);

		void set_spot_light_position(vec3 pos);
		void set_spot_light_direction(vec3 dir);
		void set_spot_light_params(vec3 ambient, vec3 diffuse, vec3 specular);
		void set_spot_light_params(float linear, float quadratic);
		void set_spot_light_inner_cut_off(float cutOff);
		void set_spot_light_outer_cut_off(float cutOff);

		void render(Shader* sh);
	};

} // !lgh

#endif // !GAME_LIGHT_SETTINGS_H_
