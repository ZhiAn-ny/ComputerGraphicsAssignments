#pragma once
#include "Lib.h"
#include "SceneObject.h"

class Scene
{
private:
	vector<SceneObject> _scene;

	void createVertexArray(SceneObject* fig);
	void bindVerticesGeometry(SceneObject* fig);
	void bindVerticesColor(SceneObject* fig);
	int getSceneLength();
	SceneObject* getObject(std::string name);

public:
	Scene();
	~Scene();

	vector<SceneObject> getScene();
	void addObject(SceneObject* fig);
	void drawScene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection);
	void transformObject(std::string name, vec3 translationVector, vec3 rotationVector, vec3 scaleVector, GLfloat angle);
};
