#ifndef GAME_LIGHT_POINT_H_
#define GAME_LIGHT_POINT_H_

#include "alight.h"

namespace lgh {

	enum class distanceCovered {
		p7
	};

	class PointLight: public ALight {
	private:
		vec3 src_pos_ = vec3(0);

		float constant_ = 1.0;
		float linear_ = 0;
		float quadratic_ = 0;

	public:
		PointLight();
		PointLight(string name);
		~PointLight();

		vec3 get_position();
		void set_position(vec3 pos);
		/* Set parameters to influence the area illuminated by the light.
		   Distance:
			 7:    linear_ = 0.7;    quadratic_ = 1.8;
			 13:   linear_ = 0.35;   quadratic_ = 0.44;
			 20:   linear_ = 0.22;   quadratic_ = 0.2;
			 32:   linear_ = 0.14;   quadratic_ = 0.07;
			 50:   linear_ = 0.09;   quadratic_ = 0.032;
			 65:   linear_ = 0.07;   quadratic_ = 0.017;
			 100:  linear_ = 0.045;  quadratic_ = 0.0075;
			 160:  linear_ = 0.027;  quadratic_ = 0.0028;
			 200:  linear_ = 0.022;  quadratic_ = 0.0019;
			 325:  linear_ = 0.014;  quadratic_ = 0.0007;
			 600:  linear_ = 0.007;  quadratic_ = 0.0002;
			 3250: linear_ = 0.0014; quadratic_ = 0.000007;
		 */
		void set_params(float linear, float quadratic);
		void render(Shader* sh, string uvar) override;
	};

}

#endif // !GAME_LIGHT_POINT_H_
