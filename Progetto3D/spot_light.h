#ifndef GAME_LIGHT_SPOTLIGHT_H_
#define GAME_LIGHT_SPOTLIGHT_H_

#include "point_light.h"

namespace lgh {

	class Spotlight: public PointLight {
	private:
		vec3 direction_ = vec3(0);
		float inner_cutOff_ = 0;
		float outer_cutOff_ = 0;

	public:
		Spotlight();
		Spotlight(string name);
		~Spotlight();

		void set_direction(vec3 dir);
		void set_inner_cutOff(float cutOff);
		void set_outer_cutOff(float cutOff);
		void render(Shader* sh, string uvar) override;
	};

}

#endif // !GAME_LIGHT_SPOTLIGHT_H_