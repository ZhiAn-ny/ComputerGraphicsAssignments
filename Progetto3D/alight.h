#ifndef GAME_LIGHT_INTERFACE_H_
#define GAME_LIGHT_INTERFACE_H_

#include "lib.h"
#include "shader.h"

namespace lgh {

	class ALight {
	private:
		string name_ = "";
		vec3 ambient_ = vec3(0.2);
		vec3 diffuse_ = vec3(0.5);
		vec3 specular_ = vec3(1);

	public:
		string get_name() { return this->name_; }
		void set_name(string name) { this->name_ = name; }

		vec3 get_ambient() { return this->ambient_; }
		vec3 get_specular() { return this->specular_; }
		vec3 get_diffuse() { return this->diffuse_; }

		void set_lights(vec3 ambient, vec3 diffuse, vec3 specular)
		{
			this->ambient_ = ambient;
			this->diffuse_ = diffuse;
			this->specular_ = specular;
		}
		virtual void render(Shader* sh) = 0;
	};

} // !lgh

#endif // !GAME_LIGHT_INTERFACE_H_
