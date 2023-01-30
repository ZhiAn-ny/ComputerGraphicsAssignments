#ifndef GAME_LIGHT_SETTINGS_H_
#define GAME_LIGHT_SETTINGS_H_

#include "lib.h"
#include "res.h"
#include "utils.h"
#include "shader.h"
#include "point_light.h"


namespace lgh {

	class LightingSettings {
	private:
		PointLight point = {};

	public:
		LightingSettings();
		~LightingSettings();

		void set_point_light_position(vec3 pos);
		void set_point_light_params(vec3 ambient, vec3 diffuse, vec3 specular);
		void render(Shader* sh);
	};

} // !lgh

#endif // !GAME_LIGHT_SETTINGS_H_
