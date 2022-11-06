#pragma once
#include "Lib.h"
#include "SceneObject.h"
#include "ShaderMaker.h"

class Scene
{
private:
	unsigned int programId;
	vector<SceneObject> _scene;
	bool isWireframeActive;

	void createVertexArray(SceneObject* fig);
	void bindVerticesGeometry(SceneObject* fig);
	void bindVerticesColor(SceneObject* fig);
	int getSceneLength();
	SceneObject* getObject(std::string name);

public:
	Scene();
	~Scene();

	vector<SceneObject> getScene();
	unsigned int getProgramID();

	void addObject(SceneObject* fig);
	void drawScene(unsigned int* MatMod, unsigned int* MatProj, mat4* Projection);
	void setShaders(char* vertexShader, char* fragmentShader);
	void transformObject(std::string name, vec3 translationVector, vec3 rotationVector, vec3 scaleVector, GLfloat angle);
};
