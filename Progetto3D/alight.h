#ifndef GAME_LIGHT_ABSTRACT_H_
#define GAME_LIGHT_ABSTRACT_H_

#include "lib.h"
#include "utils.h"
#include "shader.h"

namespace lgh {

	class ALight {
	private:
		string name_ = "";
		vec3 ambient_ = vec3(0.2);
		vec3 diffuse_ = vec3(0.5);
		vec3 specular_ = vec3(1);
		bool is_on = true;

	public:
		string get_name();
		void set_name(string name);

		void turn_on();
		void turn_off();

		vec3 get_ambient();
		vec3 get_specular();
		vec3 get_diffuse();

		void set_ambient(vec3 color);
		void set_diffuse(vec3 color);
		void set_specular(vec3 color);
		void set_lights(vec3 ambient, vec3 diffuse, vec3 specular);
		void set_color(vec3 color);

		virtual void render(Shader* sh, string uvar) = 0;
	};

} // !lgh

#endif // !GAME_LIGHT_ABSTRACT_H_
