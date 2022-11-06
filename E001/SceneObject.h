#pragma once
#include <string>
#include "Lib.h"

typedef struct {
public:
	std::string name;

	GLuint VertexArrayObject;
	GLuint VertexBufferObject_Geometry;
	GLuint VertexBufferObject_Colors;

	vector<vec3> vertices;
	vector<vec4> colors;

	int nTriangles;
	int nVertices;

	vec3 pos;

	vec3 bottomLeft;
	vec3 topRight;

	// Model matrix: translation * rotation * scale
	mat4 Model;
} SceneObject;