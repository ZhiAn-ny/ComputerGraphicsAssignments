#include "ShapeFactory.h"

ShapeFactory::ShapeFactory()
{
}

ShapeFactory::~ShapeFactory()
{
}

void ShapeFactory::getHeart(float cx, float cy, float raggiox, float raggioy, SceneObject* fig)
{
	int i;
	float stepA = (2 * PI) / fig->nTriangles;
	float t;

	// riempio il vettore mettendo prima il centro
	fig->vertices.push_back(vec3(cx, cy, 0.0));

	fig->colors.push_back(vec4(255.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
		fig->vertices.push_back(vec3(cx + raggiox * (16 * pow(sin(t), 3)) / 16, cy + raggioy * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16), 0.0));
		//Colore 
		fig->colors.push_back(vec4(1.0, 204.0 / 255.0, 0.0, 1.0));


	}
	fig->nVertices = fig->vertices.size();
}

void ShapeFactory::getButterfly(float cx, float cy, float raggiox, float raggioy, SceneObject* fig)
{
	int i;
	float stepA = (2 * PI) / fig->nTriangles;
	float t;


	fig->vertices.push_back(vec3(cx, cy, 0.0));

	fig->colors.push_back(vec4(150.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));

	for (i = 0; i <= fig->nTriangles; i++)
	{
		t = (float)i * stepA;
		fig->vertices.push_back(vec3(cx + raggiox * (sin(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4, cy + raggioy * (cos(t) * (exp(cos(t)) - 2 * cos(4 * t)) + pow(sin(t / 12), 5)) / 4, 0.0));
		//Colore 
		fig->colors.push_back(vec4(1.0, 0.0, 0.0, 0.0));


	}
	fig->nVertices = fig->vertices.size();
}
