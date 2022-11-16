#ifndef GAME_SHAPE_FACTORY_H_
#define GAME_SHAPE_FACTORY_H_

#define _USE_MATH_DEFINES

#include <math.h>

#include "scene_object.h"
#include "hermite.h"
#include "colors.h"


namespace gsf {

	class ShapeFactory {
	private:
		unsigned int heartCounter = 0;
		unsigned int butterflyCounter = 0;
		unsigned int circleCounter = 0;

		gso::SceneObject new_shape(float centerX, float centerY, float rayX, 
			float rayY, float(*xFunc)(float, float, float), 
			float(*yFunc)(float, float, float));

		gso::SceneObject new_shape(float centerX, float centerY, float rayX, 
			float rayY, float(*xFunc)(float, float, float), 
			float(*yFunc)(float, float, float), std::string name);

		gso::HermiteShape new_hermite(std::vector<glm::vec3> cp, std::string name);

		gso::HermiteShape new_hermite(std::vector<glm::vec3> cp, std::vector<glm::vec3> tbc, std::string name);

	public:
		ShapeFactory();
		~ShapeFactory();

		gso::SceneObject get_heart(float centerX, float centerY, float rayX, float rayY);

		gso::SceneObject get_butterfly(float centerX, float centerY, float rayX, float rayY);

		gso::SceneObject get_circle(float centerX, float centerY, float rayX, float rayY);
	
		gso::SceneObject get_dragon_wing();
		gso::SceneObject get_dragon_head();
		gso::SceneObject get_dragon_tail();
		gso::SceneObject get_dragon_body();
	};

}

#endif // !GAME_SHAPE_FACTORY_H_
