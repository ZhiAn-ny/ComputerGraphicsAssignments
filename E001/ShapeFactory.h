#pragma once
#include "scene_object.h"

#define PI 3.14159265358979323846264

class ShapeFactory
{
private:
	unsigned int heartCounter;
	unsigned int butterflyCounter;
	unsigned int circleCounter;

	gso::SceneObject getShape(float centerX, float centerY, float rayX, float rayY, float(*xFunc)(float, float, float), float(*yFunc)(float, float, float));
	
	void setColor(gso::SceneObject* fig, vec4 center, vec4(*colorFunc)(gso::SceneObject, int));
	
	/** Compares the last added vertex to the object's top left and bottom right
	 * corners. If the new vertex is out of the object's boundary, updates the
	 * object's corners.
	 */
	void setCorners(gso::SceneObject* fig);

public:
	ShapeFactory();
	~ShapeFactory();

	gso::SceneObject getHeart(float centerX, float centerY, float rayX, float rayY);

	gso::SceneObject getButterfly(float centerX, float centerY, float rayX, float rayY);

	gso::SceneObject getCircle(float centerX, float centerY, float rayX, float rayY);
};
