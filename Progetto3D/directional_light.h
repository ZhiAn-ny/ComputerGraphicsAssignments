#ifndef GAME_LIGHT_DIRECTIONAL_H_
#define GAME_LIGHT_DIRECTIONAL_H_

#include "alight.h"

namespace lgh {

	class DirectionalLight : public ALight {
	private:
		vec3 direction_ = vec3(0);
	
	public:
		DirectionalLight();
		DirectionalLight(string name);
		~DirectionalLight();

		void set_direction(vec3 dir);
		void render(Shader* sh, string uvar) override;
	
	};

} // !lgh

#endif // !GAME_LIGHT_DIRECTIONAL_H_
