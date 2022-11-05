#include "ShapeFactory.h"

ShapeFactory::ShapeFactory()
{
}

ShapeFactory::~ShapeFactory()
{
}

SceneObject ShapeFactory::getHeart(float centerX, float centerY, float rayX, float rayY)
{
	SceneObject fig = {};
	fig.nTriangles = 180;
	int index;
	float step = (2 * PI) / fig.nTriangles;
	float theta;

	// riempio il vettore mettendo prima il centro
	fig.vertices.push_back(vec3(centerX, centerY, 0.0));

	fig.colors.push_back(vec4(255.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (index = 0; index <= fig.nTriangles; index++)
	{
		theta = (float)index * step;
		fig.vertices.push_back(vec3(centerX + rayX * (16 * pow(sin(theta), 3)) / 16,
									 centerY + rayY * ((13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta)) / 16),
									 0.0));
		//Colore 
		fig.colors.push_back(vec4(1.0, 204.0 / 255.0, 0.0, 1.0));
	}
	fig.nVertices = fig.vertices.size();
	return fig;
}

SceneObject ShapeFactory::getButterfly(float centerX, float centerY, float rayX, float rayY)
{
	SceneObject fig = {};
	fig.nTriangles = 180;
	int index;
	float step = (2 * PI) / fig.nTriangles;
	float theta;

	fig.vertices.push_back(vec3(centerX, centerY, 0.0));

	fig.colors.push_back(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (index = 0; index <= fig.nTriangles; index++)
	{
		theta = (float)index * step;
		fig.vertices.push_back(vec3(centerX + rayX * (sin(theta) * (exp(cos(theta)) - 2 * cos(4 * theta)) + pow(sin(theta / 12), 5)) / 4,
									 centerY + rayY * (cos(theta) * (exp(cos(theta)) - 2 * cos(4 * theta)) + pow(sin(theta / 12), 5)) / 4,
									 0.0));
		//Colore 
		fig.colors.push_back(vec4(1.0, 0.0, 0.0, 0.0));
	}
	fig.nVertices = fig.vertices.size();
	return fig;
}
