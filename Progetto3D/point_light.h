#ifndef GAME_LIGHT_POINT_H_
#define GAME_LIGHT_POINT_H_

#include "alight.h"

namespace lgh {

	class PointLight: public ALight {
	private:
		vec3 src_pos_ = vec3(0);

	public:
		PointLight();
		PointLight(string name);
		~PointLight();

		vec3 get_position();
		void set_position(vec3 pos);
		void render(Shader* sh) override;
	};

}

#endif // !GAME_LIGHT_POINT_H_
