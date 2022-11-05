#pragma once
#include "Lib.h"


#define PI 3.14159265358979323846264

typedef struct {
public:
	GLuint VertexArrayObject;
	GLuint VertexBufferObject_Geometry;
	GLuint VertexBufferObject_Colors;

	vector<vec3> vertices;
	vector<vec4> colors;

	int nTriangles;
	int nVertices;

	vec3 bottomLeft;
	vec3 topRight;

	// Model matrix: translation * rotation * scale
	mat4 Model;
} SceneObject;

class ShapeFactory
{
public:
	ShapeFactory();
	~ShapeFactory();

	void getHeart(float cx, float cy, float raggiox, float raggioy, SceneObject* fig);
	void getButterfly(float cx, float cy, float raggiox, float raggioy, SceneObject* fig);
};
