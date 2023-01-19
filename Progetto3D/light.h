#ifndef GAME_LIGHT_H_
#define GAME_LIGHT_H_

#include "lib.h"
#include "res.h"

namespace lgh
{

	class Light {
	private:
		vec3 color_ = vec3(1);
		float pwr_ = 1;

	public:
		Light();
		~Light();

		vec3 get_color();
		void set_color(vec3 color);
		float get_intensity();
		void set_intensity(float i);
	};

} // !lgh

#endif // ! GAME_LIGHT_H_
