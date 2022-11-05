#include "ShapeFactory.h"

ShapeFactory::ShapeFactory()
{
	this->heartCounter = 0;
	this->butterflyCounter = 0;
}

ShapeFactory::~ShapeFactory()
{
}

SceneObject ShapeFactory::getShape(float centerX, float centerY,
								   float rayX, float rayY,
								   float (*xFunc)(float, float, float),
								   float (*yFunc)(float, float, float))
{
	SceneObject fig = {};
	int index;
	float step;
	float theta, x, y;

	fig.nTriangles = 180;
	step = (2 * PI) / fig.nTriangles;

	// Add central vertex to the figure
	fig.vertices.push_back(vec3(centerX, centerY, 0.0));
	fig.colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));

	// Add all the other vertices on the perimeter
	for (index = 0; index <= fig.nTriangles; index++)
	{
		theta = (float)index * step;
		x = xFunc(centerX, rayX, theta);
		y = yFunc(centerY, rayY, theta);

		fig.vertices.push_back(vec3(x, y, 0.0));
		//Colors
		fig.colors.push_back(vec4(1.0, 1.0, 1.0, 1.0));
	}
	fig.nVertices = fig.vertices.size();

	return fig;
}

void ShapeFactory::setColor(SceneObject* fig, vec4 center, vec4(*colorFunc)(SceneObject, int))
{
	int index = 0;

	fig->colors[index] = center;

	// Add all the other vertices on the perimeter
	for (index = 1; index < fig->colors.size(); index++)
	{
		fig->colors[index] = colorFunc(*fig, index);
	}
}

SceneObject ShapeFactory::getHeart(float centerX, float centerY, float rayX, float rayY)
{
	SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (16 * pow(sin(t), 3)) / 16);},
		[](float y, float r, float t) {return y + r * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16);});

	fig.name = "heart_";
	fig.name += std::to_string(this->heartCounter);

	this->setColor(&fig, vec4(255.0 / 255.0, 75.0 / 255.0, 0.0, 1.0),
		[](SceneObject f, int i) {return vec4(1.0, 204.0 / 255.0, 0.0, 1.0);});

	this->heartCounter++;
	return fig;
}

SceneObject ShapeFactory::getButterfly(float centerX, float centerY, float rayX, float rayY)
{
	SceneObject fig = this->getShape(centerX, centerY, rayX, rayY,
		[](float x, float r, float t) {return (float)(x + r * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); },
		[](float y, float r, float t) {return (float)(y + r * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4); });

	fig.name = "butterfly_";
	fig.name += std::to_string(this->butterflyCounter);

	this->setColor(&fig, vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0),
		[](SceneObject f, int i) {return vec4(1.0, 0.0, 0.0, 0.0); });

	this->butterflyCounter++;
	return fig;
}
