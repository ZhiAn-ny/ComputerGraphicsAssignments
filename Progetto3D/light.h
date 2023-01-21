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

		vec3 get_color() { return this->color_; }
		void set_color(vec3 color) { this->color_ = color; }
		float get_intensity() { return this->pwr_; }
		void set_intensity(float i) { this->pwr_ = i; }
	};

	class PointLight : public Light {
	private:
		vec3 pos_ = vec3(0);

	public:
		PointLight();
		~PointLight();

		vec3 get_position() { return this->pos_; }
		void set_position(vec3 pos) { this->pos_ = pos; }
	};

} // !lgh

#endif // ! GAME_LIGHT_H_
