#ifndef GAME_LIGHT_SPOTLIGHT_H_
#define GAME_LIGHT_SPOTLIGHT_H_

#include "point_light.h"

namespace lgh {

	class Spotlight: public PointLight {
	private:
		vec3 direction_ = vec3(0);
		float cutOff_ = 0;

	public:
		Spotlight();
		~Spotlight();

		void set_direction(vec3 dir);
		void set_cut_off(float cutOff);
		void render(Shader* sh) override;
	};

}

#endif // !GAME_LIGHT_SPOTLIGHT_H_