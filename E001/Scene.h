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

public:
	Scene();
	~Scene();

	vector<SceneObject> getScene();
	void addObject(SceneObject* fig);
	void drawScene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection);

};
