#ifndef GAME_LIGHT_DIRECTIONAL_H_

#include "alight.h"

namespace lgh {

	class DirectionalLight : public ALight {
	private:
		vec3 direction_ = vec3(0);
	
	public:
		DirectionalLight();
		~DirectionalLight();

		void set_direction(vec3 dir);
		void render(Shader* sh);
	
	};

} // !lgh

#endif // !GAME_LIGHT_DIRECTIONAL_H_
