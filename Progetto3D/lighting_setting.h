#ifndef GAME_LIGHT_SETTINGS_H_
#define GAME_LIGHT_SETTINGS_H_

#include "lib.h"
#include "res.h"
#include "utils.h"
#include "shader.h"


namespace lgh {

	class LightingSettings {
	private:
		vec3 src_pos;

		vec3 ambient_ = vec3(0.2);
		vec3 diffuse_ = vec3(0.5);
		vec3 specular_ = vec3(1);

	public:
		LightingSettings();
		~LightingSettings();

		void set_position(vec3 pos);
		void set_lights(vec3 ambient, vec3 diffuse, vec3 specular);
		void render(Shader* sh);
	};

} // !lgh

#endif // !GAME_LIGHT_SETTINGS_H_
