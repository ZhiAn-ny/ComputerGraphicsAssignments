#ifndef GAME_SHAPE_FACTORY_H_
#define GAME_SHAPE_FACTORY_H_

#include "scene_object.h"
#include "colors.h"

namespace gsf {

	const float pi = 3.14159265358979323846264;

	class ShapeFactory {
	private:
		unsigned int heartCounter = 0;
		unsigned int butterflyCounter = 0;
		unsigned int circleCounter = 0;

		gso::SceneObject getShape(float centerX, float centerY, float rayX, 
			float rayY, float(*xFunc)(float, float, float), 
			float(*yFunc)(float, float, float));

		gso::SceneObject getShape(float centerX, float centerY, float rayX, 
			float rayY, float(*xFunc)(float, float, float), 
			float(*yFunc)(float, float, float), std::string name);

	public:
		ShapeFactory();
		~ShapeFactory();

		gso::SceneObject getHeart(float centerX, float centerY, float rayX, float rayY);

		gso::SceneObject getButterfly(float centerX, float centerY, float rayX, float rayY);

		gso::SceneObject getCircle(float centerX, float centerY, float rayX, float rayY);
	};

}

#endif // !GAME_SHAPE_FACTORY_H_
