#pragma once
#include "SceneObject.h"

#define PI 3.14159265358979323846264

class ShapeFactory
{
private:
	unsigned int heartCounter;
	unsigned int butterflyCounter;
	unsigned int circleCounter;

	SceneObject getShape(float centerX, float centerY, float rayX, float rayY, float(*xFunc)(float, float, float), float(*yFunc)(float, float, float));
	void setColor(SceneObject* fig, vec4 center, vec4(*colorFunc)(SceneObject, int));

public:
	ShapeFactory();
	~ShapeFactory();

	SceneObject getHeart(float centerX, float centerY, float rayX, float rayY);
	SceneObject getButterfly(float centerX, float centerY, float rayX, float rayY);
	SceneObject getCircle(float centerX, float centerY, float rayX, float rayY);
};
